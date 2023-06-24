#include "header.h"

using namespace llvm;

bool isDroppableInstruction(Instruction *I)
{
    if (CallInst *CI = dyn_cast<CallInst>(I))
    {
        if (Function *Callee = CI->getCalledFunction())
        {
            if (Callee->getName() == "printf")
            {
                return false; // Non considerare printf come codice eliminabile
            }
        }
    }
    return I->use_empty() && !I->isTerminator();
}

void runDCEblock(BasicBlock &B)
{
    bool removed;
    do
    {
        removed = false;
        std::vector<Instruction *> to_remove;

        for (Instruction &I : B)
        {
            if (isDroppableInstruction(&I))
            {
                to_remove.push_back(&I);
            }
        }

        for (Instruction *I : to_remove)
        {
            I->eraseFromParent();
            removed = true;
        }
    } while (removed);
}

PreservedAnalyses DeadCodeElimination::run(Module &M, ModuleAnalysisManager &MAM)
{
    outs() << "__ DEAD CODE ELIMINATION __\n";
    print(M);
    for (Function &F : M)
    {
        for (BasicBlock &B : F)
        {
            runDCEblock(B);
        }
    }
    print(M);
    return PreservedAnalyses::none();
}