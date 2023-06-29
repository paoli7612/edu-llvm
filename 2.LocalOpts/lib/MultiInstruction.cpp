#include "LocalOpts.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include <vector>

using namespace llvm;

static bool areOperationCodesOpposite(unsigned int opcode1, unsigned int opcode2)
{
    if (opcode1 == Instruction::Add && opcode2 == Instruction::Sub)
    {
        return true;
    }
    else if (opcode1 == Instruction::Sub && opcode2 == Instruction::Add)
    {
        return true;
    }

    return false;
}

static bool runMIblock(BasicBlock &b)
{
    for (Instruction &i : b)
    {
        if (i.getNumOperands() != 2)
        {
            continue;
        }

        BinaryOperator *binaryOperation = dyn_cast<BinaryOperator>(i.getOperand(0));
        ConstantInt *constant = dyn_cast<ConstantInt>(i.getOperand(1));

        if (!constant || !binaryOperation)
        {
            continue;
        }

        auto binaryOperationConstant = dyn_cast<ConstantInt>(binaryOperation->getOperand(1));

        if (binaryOperationConstant != constant)
        {
            continue;
        }

        auto operationCode = i.getOpcode();
        auto binaryOperationOpcode = binaryOperation->getOpcode();

        if (areOperationCodesOpposite(operationCode, binaryOperationOpcode))
        {
            if (constant->getValue() == binaryOperationConstant->getValue())
            {
                i.replaceAllUsesWith(binaryOperation->getOperand(0));
            }
        }
    }
    return true;
}

PreservedAnalyses MultiInstructionPass::run([[maybe_unused]] Module &M, ModuleAnalysisManager &Mum)
{
    print(M);
    outs() << "__ Let's do MULTI INSTRUCTION __\n";
    for (Function &f : M)
    {
        for (BasicBlock &b : f)
        {
            runMIblock(b);
        }
    }
    print(M);
    return PreservedAnalyses::none();
}
