#include "LocalOpts.h"

using namespace llvm;

void print(Instruction &i) {
  outs() << "\t\t<instruction>\t" << i << "\n";
}

void print(BasicBlock &b) {
  outs() << "\t<basic block>\n"; 
  for (Instruction &i: b) {
    print(i);
  }
}

void print(Function &f) {
  outs() << "<function " << f.getName() << ">\n";
  for (BasicBlock &b: f) {
    print(b);
  }
}

void print(Module &m) {
  for (Function &f: m) {
    print(f);
  }
}

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo()
{
  return {
      .APIVersion = LLVM_PLUGIN_API_VERSION,
      .PluginName = "LocalOpts",
      .PluginVersion = LLVM_VERSION_STRING,
      .RegisterPassBuilderCallbacks =
          [](PassBuilder &PB)
      {
        PB.registerPipelineParsingCallback(
            // CREO LO STUB per Transform
            //
            // RICORDA: Posso usare (coi relativi Pass Managers)
            // -------------------------------------------------
            // ModulePass
            // CallGraphSCCPass
            // FunctionPass
            // LoopPass
            // RegionPass
            // BasicBlockPass
            [](StringRef Name, ModulePassManager &MPM,
               ArrayRef<PassBuilder::PipelineElement>) -> bool
            {
              if (Name == "transform")
              {
                MPM.addPass(TransformPass());
                return true;
              }
              // TODO: Implementare gli stub per
              // Algebraic Identity
              // Strength Reduction
              // Multi-instruction Operations
              return false;
            });
        PB.registerPipelineParsingCallback(
            // CREO LO STUB per Algebraic
            [](StringRef Name, ModulePassManager &MPM,
               ArrayRef<PassBuilder::PipelineElement>) -> bool
            {
              if (Name == "algebraic-identity")
              {
                MPM.addPass(AlgebraicIdentityPass());
                return true;
              }
              return false;
            });
      } // RegisterPassBuilderCallbacks
  };    // struct PassPluginLibraryInfo
}
