#include "header.h"

using namespace llvm;

void runCPblock(BasicBlock &b) {
    std::map<Value *, Constant *> constantMap;

    for (Instruction &i : b) {
        if (i.isBinaryOp()) {
            ConstantInt *c0 = dyn_cast<ConstantInt>(i.getOperand(0));
            ConstantInt *c1 = dyn_cast<ConstantInt>(i.getOperand(1));
            
            if (c0 && c1) {
                APInt result;
                switch (i.getOpcode()) {
                    case Instruction::Add:
                        result = c0->getValue() + c1->getValue();
                        break;
                }
                constantMap[&i] = ConstantInt::get(i.getType(), result);
            }
        }
    }

    std::vector<Instruction *> toRemove;

    for (Instruction &i : b) {
        if (constantMap.count(&i)) {
            if (i.use_empty()) {
                toRemove.push_back(&i);
            } else {
                i.replaceAllUsesWith(constantMap[&i]);
                toRemove.push_back(&i);
            }
        }
    }

    // Remove instructions that have been replaced
    for (Instruction *i : toRemove) {
        i->eraseFromParent();
    }
}

PreservedAnalyses ConstantPass::run(Module &M, ModuleAnalysisManager &MAM)
{
    print(M);
    outs() << "__ Let's do CONSTANT Propagation and Folding __\n";
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