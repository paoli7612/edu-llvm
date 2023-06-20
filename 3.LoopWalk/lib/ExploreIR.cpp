#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
class ExploreIR final : public PassInfoMixin<ExploreIR>
{
public:
    PreservedAnalyses run([[maybe_unused]] Module &M, ModuleAnalysisManager &)
    {
        outs() << "Module '" << M.getName() << "'\n";
        for (Function &F: M) {
            outs() << "\t Function '" << F.getName() << "'\n";
            for (BasicBlock &B: F) {
                outs() << "\t\t BasicBlock" << "\n";
                for (Instruction &I: B) {
                    outs() << "\t\t\t Instruction" << "\t";
                    I.printAsOperand(outs());
                    outs() << "\n";
                }
            }
        }
        return PreservedAnalyses::all();
    }
};
extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo()
{
    return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "ExploreIR",
        .PluginVersion = LLVM_VERSION_STRING,
        .RegisterPassBuilderCallbacks =
            [](PassBuilder &PB)
        {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) -> bool
                {
                    if (Name == "explore-ir")
                    {
                        MPM.addPass(ExploreIR());
                        return true;
                    }
                    return false;
                });
        }};
}
