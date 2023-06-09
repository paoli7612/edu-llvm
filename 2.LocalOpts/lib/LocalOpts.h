#pragma once // NOLINT(llvm-header-guard)

#include <llvm/IR/PassManager.h>
#include <llvm/IR/Constants.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

#include "llvm/IR/InstrTypes.h"

class TransformPass final : public llvm::PassInfoMixin<TransformPass> {
  public: llvm::PreservedAnalyses run(llvm::Module &, llvm::ModuleAnalysisManager &);
};

class AlgebraicIdentityPass final : public llvm::PassInfoMixin<AlgebraicIdentityPass> {
  public: llvm::PreservedAnalyses run(llvm::Module &, llvm::ModuleAnalysisManager &);
};
