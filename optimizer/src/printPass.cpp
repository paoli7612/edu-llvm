#include "header.h"

using namespace llvm;

PreservedAnalyses PrintPass::run([[maybe_unused]] Module &M, ModuleAnalysisManager &Mum)
{
    outs() << "__ PRINT __\n";
    print(M);
    return PreservedAnalyses::none();
}

