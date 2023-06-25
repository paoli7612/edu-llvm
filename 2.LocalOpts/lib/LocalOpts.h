#pragma once // NOLINT(llvm-header-guard)

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Constants.h>
#include "llvm/IR/InstrTypes.h"
#include <cmath>
#include <cstdint>
#include <math.h>
#include <string.h>


using namespace llvm;


class TransformPass final : public PassInfoMixin<TransformPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

class AlgebraicIdentityPass final : public PassInfoMixin<AlgebraicIdentityPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

class StrengthReductionPass final : public PassInfoMixin<StrengthReductionPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

class MultiInstructionPass final : public PassInfoMixin<MultiInstructionPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

void print(Instruction &i);
void print(BasicBlock &b);
void print(Function &f);
void print(Module &m);