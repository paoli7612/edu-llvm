#include "LocalOpts.h"

using namespace llvm;

void runSRmulInstr(ConstantInt *C0, ConstantInt *C1, LLVMContext &c, Instruction &i)
{

    if (C0)
    {
        if (C0->getValue().isPowerOf2())
        {
            Instruction *new_i = BinaryOperator::CreateShl(i.getOperand(1), ConstantInt::get(C0->getType(), C0->getValue().logBase2()));
            new_i->insertAfter(&i);
            i.replaceAllUsesWith(new_i);
        }
    }
    else if (C1)
    {
        if (C1->getValue().isPowerOf2())
        {
            Instruction *new_i = BinaryOperator::CreateShl(i.getOperand(0), ConstantInt::get(C1->getType(), C1->getValue().logBase2()));
            new_i->insertAfter(&i);
            i.replaceAllUsesWith(new_i);
        }
    }
}

void runSRdivInstr(ConstantInt *C1, Instruction &i)
{
    if (C1 && !C1->getValue().isZero())
    {
        if (C1->getValue().isPowerOf2())
        {
            Instruction *newInst = BinaryOperator::CreateLShr(i.getOperand(0), ConstantInt::get(C1->getType(), C1->getValue().logBase2()));
            newInst->insertAfter(&i);
            i.replaceAllUsesWith(newInst);
        }
    }
}

void runSRblock(BasicBlock &b)
{
    Function *F = b.getParent();
    LLVMContext &context = F->getContext();

    for (Instruction &i : b)
    {
        if (i.getNumOperands() == 2)
        {
            ConstantInt *C0 = dyn_cast<ConstantInt>(i.getOperand(0));
            ConstantInt *C1 = dyn_cast<ConstantInt>(i.getOperand(1));
            if (i.getOpcode() == Instruction::Mul)
            {
                runSRmulInstr(C0, C1, context, i);
            }
            if (i.getOpcode() == Instruction::SDiv)
            {
                runSRdivInstr(C1, i);
            }
        }
    }
}

PreservedAnalyses StrengthReductionPass::run([[maybe_unused]] Module &M, ModuleAnalysisManager &Mam)
{
    print(M);
    for (Function &f : M)
    {
        for (BasicBlock &b : f)
        {
            runSRblock(b);
        }
    }
    print(M);
    return PreservedAnalyses::none();
}
