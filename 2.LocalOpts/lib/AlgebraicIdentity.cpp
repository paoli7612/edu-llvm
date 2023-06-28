#include "LocalOpts.h"

using namespace llvm;

void runAIblock(BasicBlock &b)
{
    std::vector<Instruction*> to_remove;

    for (Instruction &i : b)
    {
        if (i.getNumOperands() == 2)
        {
            ConstantInt *C0 = dyn_cast<ConstantInt>(i.getOperand(0));
            ConstantInt *C1 = dyn_cast<ConstantInt>(i.getOperand(1));
            if (i.getOpcode() == Instruction::Add)
            {
                if (C0 && (C0->getValue()).isZero())
                {
                    i.replaceAllUsesWith(i.getOperand(1));
                    to_remove.push_back(&i);
                }
                else if (C1 && (C1->getValue()).isZero())
                {
                    i.replaceAllUsesWith(i.getOperand(0));
                    to_remove.push_back(&i);
                }
            }
            else if (i.getOpcode() == Instruction::Mul)
            {
                if (C0 && C0->getValue().isOneValue())
                {
                    i.replaceAllUsesWith(i.getOperand(1));
                    to_remove.push_back(&i);
                }
                else if (C1 && C1->getValue().isOneValue())
                {
                    i.replaceAllUsesWith(i.getOperand(0));
                    to_remove.push_back(&i);
                }
            }
        }
    }

    for (Instruction *i : to_remove) {
        i->eraseFromParent();
    }
}


PreservedAnalyses AlgebraicIdentityPass::run([[maybe_unused]] Module &M, ModuleAnalysisManager &Mum)
{
    print(M);
    outs() << "__ Let's do ALGEBRAIC IDENTITY __\n";
    for (Function &f : M)
    {
        for (BasicBlock &b : f)
        {
            runAIblock(b);
        }
    }
    print(M);
    return PreservedAnalyses::none();
}

