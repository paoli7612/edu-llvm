#include "header.h"

using namespace llvm;

void runCPblock(BasicBlock &b) {
    std::map<Value *, Constant *> constantMap;

    for (Instruction &i : b) {
        if (i.isBinaryOp()) {
            Value *op0 = i.getOperand(0);
            Value *op1 = i.getOperand(1);

            if (ConstantInt *c0 = dyn_cast<ConstantInt>(op0)) {
                constantMap[&i] = c0;
            } else if (ConstantInt *c1 = dyn_cast<ConstantInt>(op1)) {
                constantMap[&i] = c1;
            }
        }
    }

    for (Instruction &i : b) {
        for (Use &use : i.operands()) {
            if (Instruction *inst = dyn_cast<Instruction>(use.get())) {
                if (constantMap.count(inst)) {
                    Constant *constantValue = constantMap[inst];
                    use.set(constantValue);
                }
            }
        }
    }
}

PreservedAnalyses ConstantPropagationPass::run(Module &M, ModuleAnalysisManager &MAM)
{
    outs() << "__ CONSTANT PROPAGATION __\n";
    print(M);
    for (Function &F : M)
    {
        for (BasicBlock &BB : F)
        {
            runCPblock(BB);
        }
    }
    print(M);
    return PreservedAnalyses::none();
}



