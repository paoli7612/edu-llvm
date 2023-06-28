#include <llvm/Analysis/LoopPass.h>
#include <llvm/IR/Dominators.h>
#include <llvm/Analysis/ValueTracking.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Analysis/LoopInfo.h>

using namespace llvm;

namespace
{
    class LoopFusionPass : public LoopPass
    {
    public:
        static char ID;
        LoopFusionPass() : LoopPass(ID)
        {
            llvm::initializeLoopFusionPass(*llvm::PassRegistry::getPassRegistry());
        }

        virtual void getAnalysisUsage(AnalysisUsage &AU) const override
        {
            AU.addRequired<DominatorTreeWrapperPass>();
            AU.addRequired<LoopInfoWrapperPass>();
        }

        virtual bool runOnLoop(Loop *L, LPPassManager &LPM) override
        {
            // Controlla se la loop fusion può essere eseguita
            if (canPerformLoopFusion(L))
            {
                // Esegui la loop fusion
                performLoopFusion(L);
                return true;
            }

            return false;
        }

        bool canPerformLoopFusion(Loop *L)
        {
            // Check if the loop has only a single exit block
            if (!L->getExitBlock() || L->getExitBlock() != L->getExitingBlock())
                return false;

            // Check if the loop has a single backedge
            if (L->getNumBackEdges() != 1)
                return false;

            // Check if the loop is innermost (no nested loops)
            if (!L->empty())
                return false;

            // Check if there are no instructions with side effects in the loop
            for (BasicBlock *BB : L->getBlocks())
            {
                for (Instruction &I : *BB)
                {
                    if (I.mayHaveSideEffects())
                        return false;
                }
            }

            return true;
        }

        void performLoopFusion(Loop *L)
        {
            // Ottieni le informazioni necessarie sul loop
            BasicBlock *Header = L->getHeader();
            BasicBlock *Latch = L->getLoopLatch();
            BasicBlock *Preheader = L->getLoopPreheader();
            BasicBlock *Exit = L->getExitBlock();

            // Crea un nuovo blocco che conterrà le istruzioni combinate dei cicli fusi
            BasicBlock *MergedBody = BasicBlock::Create(Header->getContext(), "MergedBody", Header->getParent(), Exit);

            // Sposta le istruzioni dai blocchi originali al nuovo blocco fuso
            for (auto *BB : L->blocks())
            {
                if (BB != Header && BB != Latch)
                {
                    MergedBody->getInstList().splice(MergedBody->end(), BB->getInstList());
                }
            }

            // Rimuovi i blocchi originali dal loop
            for (auto *BB : L->blocks())
            {
                if (BB != Header && BB != Latch)
                {
                    L->removeBlockFromLoop(BB);
                }
            }

            // Collega il preheader al nuovo blocco fuso
            BranchInst::Create(MergedBody, Preheader);

            // Aggiorna i predecessori del blocco di uscita per puntare al nuovo blocco fuso
            for (auto *Pred : predecessors(Exit))
            {
                if (Pred != Header && Pred != Latch)
                {
                    Pred->getTerminator()->replaceUsesOfWith(Exit, MergedBody);
                }
            }

            // Aggiorna le informazioni sul loop
            L->getBlocksVector().clear();
            L->getBlocksVector().push_back(Header);
            L->getBlocksVector().push_back(MergedBody);
            L->addBasicBlockToLoop(MergedBody, getAnalysis<LoopInfoWrapperPass>().getLoopInfo());
        }
    };

    char LoopFusionPass::ID = 0;
    RegisterPass<LoopFusionPass> X("lofu", "Loop Fusion");
} // anonymous namespace