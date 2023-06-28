#include <llvm/Analysis/LoopPass.h>
#include <llvm/IR/Dominators.h>
#include <llvm/Analysis/ValueTracking.h>
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;

namespace
{

    class LoopWalkPass final : public LoopPass
    {
    public:
        static char ID;

        LoopWalkPass() : LoopPass(ID) {}

        virtual void getAnalysisUsage(AnalysisUsage &AU) const override
        {
            AU.addRequired<DominatorTreeWrapperPass>();
            AU.addRequired<LoopInfoWrapperPass>();
        }

        void runOnBasicBlock(BasicBlock &b)
        {
            for (Instruction &i : b)
            {
                if (BranchInst *ib = dyn_cast<BranchInst>(&i))
                {
                    if (ib->isConditional())
                    {
                        outs() << "salto condizionale: " << i << "\n";
                    }
                    else
                    {
                        outs() << "salto incondizionale: " << i << "\n";
                    }
                }
                else
                {
                    outs() << i << "\n";
                }
            }
        }

        virtual bool runOnLoop(Loop *L, LPPassManager &LPM) override
        {
            outs() << "\nLOOPPASS INIZIATO...\n";
            if (!L->isLoopSimplifyForm())
            {
                return false;
            }
            outs() << "\n\tPREHEADER:\n";
            BasicBlock *b1 = L->getLoopPreheader();
            runOnBasicBlock(*b1);
            

            // Itero sui basic blocks del loop
            for (BasicBlock *b : L->blocks())
            {
                outs() << "\n\tBASIC BLOCK :\n";
                runOnBasicBlock(*b);

                /*
                outs() << "Scrorrendo le istruzioni del BB: \n";
                for (Instruction &Inst : *b)
                {
                    // Cerco la SUB
                    if (Inst.getOpcode() == Instruction::Sub)
                    {
                        outs() << "Istruzione SUB: " << Inst << "\n";

                        // Itero sugli operatori
                        for (Value *op : Inst.operands())
                        {
                            // Se non è una const
                            if (Instruction *arg = dyn_cast<Instruction>(op))
                            {
                                outs() << "Istruzione che definisce: " << *op << "\n";
                                outs() << "Basic Block dell'istruzione:\n" << *arg->getParent() << "\n";
                            }
                        }
                    }
                }
                */
            }
            return true;
        }
    };

    char LoopWalkPass::ID = 0;
    RegisterPass<LoopWalkPass> X("loop-walk", "Loop Walk");

} // anonymous namespace
