#include <llvm/Analysis/LoopPass.h>
#include <llvm/IR/Dominators.h>
#include <llvm/Analysis/ValueTracking.h>
#include <llvm/IR/Instructions.h>
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;

namespace
{
    class LoopWalkPass final : public LoopPass
    {
    public:
        static char ID;
        LoopWalkPass() : LoopPass(ID) {}

        // Indichiamo che il passaggio richiede il DominatorTreeWrapperPass e il LoopInfoWrapperPass
        virtual void getAnalysisUsage(AnalysisUsage &AU) const override
        {
            AU.addRequired<DominatorTreeWrapperPass>();
            AU.addRequired<LoopInfoWrapperPass>();
        }

        // determiniamo se un'istruzione è loop-invariant per un loop
        bool isLoopInvariant(Instruction &i, Loop *L)
        {
            for (Use &u : i.operands())
            {
                Value *v = u.get(); 
                // non deve essere un PHI-node
                if (isa<PHINode>(i) || isa<BranchInst>(i))
                    return false;
                // se v è un'istruzione
                if (Instruction *arg = dyn_cast<Instruction>(v)) 
                {
                    // se l'istruzione è nel loop
                    if (L->contains(arg))
                    {
                        // l'istruzione deve essere loop-invariant
                        if (!isLoopInvariant(*arg, L))
                            return false;
                    }
                }
            }
            return true;
        }

        // determiniamo se un'istruzioni domina tutti i blocchi di uscita di un loop
        bool dominatesExits(Instruction *inst, DominatorTree &DT, Loop *L)
        {
            SmallVector<BasicBlock *> exits;

            for (BasicBlock *block : L->getBlocks())
            {
                if (block != L->getHeader() && L->isLoopExiting(block))
                    exits.push_back(block);
            }

            for (BasicBlock *exit : exits)
            {
                if (!DT.dominates(inst->getParent(), exit))
                    return false;
            }

            return true;
        }

        // determiniamo se un'istruzione domina tutte le istruzioni all'interno di un dominator tree
        bool dominatesUseBlocks(DominatorTree &DT, Instruction *inst)
        {
            for (auto *useInst : inst->users())
            {
                if (!DT.dominates(inst, dyn_cast<Instruction>(useInst)))
                {
                    // appena trovo un'istruzione che non viene dominata ritorno falso
                    return false;
                }
            }
            return true;
        }

        virtual bool runOnLoop(Loop *L, LPPassManager &LPM) override
        {
            // Il loop deve essere in forma normalizzata
            if (!L->isLoopSimplifyForm())
            {
                return false;
            }

            DominatorTree *DT = &getAnalysis<DominatorTreeWrapperPass>().getDomTree();
            SmallVector<Instruction *> loopInvariantInstructions;
            SmallVector<Instruction *> movableInstruction;

            // Controlliamo se ci cono istruzioni loop invariant nei blocchi del loop
            for (BasicBlock *b : L->blocks())
            {
                for (Instruction &i : *b)
                {
                    if (isLoopInvariant(i, L))
                    {
                        loopInvariantInstructions.push_back(&i);
                        outs() << i << " -> loop-invariant\n";
                    }
                }
            }

            // Controlliamo se le loop-invariant sono anche movable
            for (Instruction *i : loopInvariantInstructions)
            {
                if (dominatesExits(i, *DT, L) && dominatesUseBlocks(*DT, i))
                    movableInstruction.push_back(i);
            }

            // Spostiamo le moovable
            BasicBlock *preHeader = L->getLoopPreheader();
            for (Instruction *i : movableInstruction)
            {
                outs() << "Trovata istruzione movable: " << *i << "\n";
                i->moveBefore(&preHeader->back());
            }
            return true;
        }
    };

    char LoopWalkPass::ID = 0;
    RegisterPass<LoopWalkPass> X("licomo", "Loop-Invariant Code Motion");

} // anonymous namespace
