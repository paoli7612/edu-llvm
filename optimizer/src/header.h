#pragma once // NOLINT(llvm-header-guard)

#include <llvm/IR/PassManager.h>
#include <llvm/IR/Constants.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include "llvm/IR/InstrTypes.h"

#include "llvm/ADT/APInt.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include <cmath>
#include <cstdint>
#include <math.h>
#include <string.h>

using namespace llvm;

class PrintPass final : public PassInfoMixin<PrintPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

class AlgebraicIdentityPass final : public PassInfoMixin<AlgebraicIdentityPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};
class StrenghtReductionPass final : public PassInfoMixin<StrenghtReductionPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};
class DeadCodeElimination final : public PassInfoMixin<DeadCodeElimination> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};
class ConstantPass final : public PassInfoMixin<ConstantPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

class LoopPass final : public PassInfoMixin<LoopPass> {
  public: PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

void print(Instruction &i);
void print(BasicBlock &b);
void print(Function &f);
void print(Module &m);