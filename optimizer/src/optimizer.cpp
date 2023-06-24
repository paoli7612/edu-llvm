#include "header.h"

using namespace llvm;

void print(Instruction &i)
{
    outs() << "\t\t<instruction>\t" << i << "\n";
}

void print(BasicBlock &b)
{
    outs() << "\t<basic block>\n";
    for (Instruction &i : b)
    {
        print(i);
    }
}

void print(Function &f)
{
    outs() << "<function " << f.getName() << ">\n";
    for (BasicBlock &b : f)
    {
        print(b);
    }
}

void print(Module &m)
{
    for (Function &f : m)
    {
        print(f);
    }
}

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo()
{
    return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "LocalOpts",
        .PluginVersion = LLVM_VERSION_STRING,
        .RegisterPassBuilderCallbacks = [](PassBuilder &PB)
        {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) -> bool
                {
                    if (Name == "algebraic-identity")
                    {
                        MPM.addPass(AlgebraicIdentityPass());
                        return true;
                    }
                    return false;
                });
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) -> bool
                {
                    if (Name == "dead-code-elimination")
                    {
                        MPM.addPass(DeadCodeElimination());
                        return true;
                    }
                    return false;
                });
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) -> bool
                {
                    if (Name == "constant-propagation")
                    {
                        MPM.addPass(ConstantPass());
                        return true;
                    }
                    return false;
                });
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) -> bool
                {
                    if (Name == "strenght-elimination")
                    {
                        MPM.addPass(StrenghtReductionPass());
                        return true;
                    }
                    return false;
                });

            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) -> bool
                {
                    if (Name == "print")
                    {
                        MPM.addPass(PrintPass());
                        return true;
                    }
                    return false;
                });
        }};
}
