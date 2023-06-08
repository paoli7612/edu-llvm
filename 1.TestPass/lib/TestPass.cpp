#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

class TestPass final : public PassInfoMixin<TestPass>
{
public:
    PreservedAnalyses run([[maybe_unused]] Module &M, ModuleAnalysisManager &)
    {
        outs() << "Passo di test per il corso di Linguaggi e Compilatori"
               << "\n\n";

    

        for (auto &function : M)
        {
            uint nCall = 0, nBlock = 0, nInstruction = 0;
            for (auto &bb : function) {
                nBlock++;
                for (auto &inst : bb) {
                    if (dyn_cast<CallBase>(&inst) != nullptr) nCall++;

                    nInstruction++;
                }
            }

            outs() << "Nome della funzione: " << function.getName() << "\n";
            auto functionType = function.getFunctionType();
            outs() << "Numero di Argomenti: " << functionType->getNumParams();
            if (functionType->isVarArg())
                outs() << "+*";
            outs() << "\n";
            outs() << "Numero chiamate: " << nCall << "\n";
            outs() << "Numero di BB: " << nBlock << "\n";
            outs() << "Numero di Instructions: " << nInstruction << "\n";
            outs() << "\n";
        }
        return PreservedAnalyses::all();
    }
}; // class TestPass

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo()
{
    return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "TestPass",
        .PluginVersion = LLVM_VERSION_STRING,
        .RegisterPassBuilderCallbacks =
            [](PassBuilder &PB)
        {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) -> bool
                {
                    if (Name == "test-pass")
                    {
                        MPM.addPass(TestPass());
                        return true;
                    }
                    return false;
                });
        }};
}
