#include "LoopFusion.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

using namespace llvm;

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo()
{
    return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "LoopFusion",
        .PluginVersion = LLVM_VERSION_STRING,
        .RegisterPassBuilderCallbacks =
            [](PassBuilder &PB)
        {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) -> bool
                {
                    if (Name == "loop-fusion")
                    {
                        FPM.addPass(LoopFusionPass());
                        return true;
                    }
                    return false;
                });
        }};
}