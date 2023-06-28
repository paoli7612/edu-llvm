/*
Estendete il passo TestPass di modo che analizzi la IR e
stampi alcune informazioni utili per ciascuna della funzioni
che compaiono nel programma di test
    Nome
    Numero di argomenti (‘N+*’ in caso di funzione variadica)(*)
    Numero di chiamate a funzione nello stesso modulo
    Numero di Basic Blocks
    Numero di Istruzioni
*/

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

class TestPass final : public PassInfoMixin<TestPass>
{
public:
    PreservedAnalyses run([[maybe_unused]] Module &m, ModuleAnalysisManager &)
    {
        outs() << "Stampiamo nome funzione, numero argomenti [+*]\n\n";
        for (Function &f : m)
        {
            int nCall = 0, nBlock = 0, nInstruction = 0;
            for (BasicBlock &b : f) {
                nBlock++;
                for (Instruction &inst : b) {
                    if (dyn_cast<CallBase>(&inst) != nullptr)
                        nCall++;
                    nInstruction++;
                }
            }


            // Nome
            outs() << "Nome: " << f.getName() << "\n";
            // Numero di argomenti (‘N+*’ in caso di funzione variadica)(*)
            auto ft = f.getFunctionType();
            outs() << "Numero di Argomenti: " << ft->getNumParams();
            if (ft->isVarArg())
                outs() << "+*";
            outs() << "\n";
            // Numero di chiamate a funzione nello stesso modulo
            outs() << "Numero chiamate: " << nCall << "\n";
            // Numero di Basic Blocks
            outs() << "Numero di BB: " << nBlock << "\n";
            // Numero di Istruzioni
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
