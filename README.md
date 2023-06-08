# 0. Explore IR
Passo di prova da usare per sperimentare come viaggiare lungo la IR.
Sono presenti 3 file generici: alfa, beta e gamma (dentro alla cartella `0.ExploreIR/test`)
Tramite il makefile possiamo generare la rappresentazione intermedia nella cartella `0.ExploreIR/ll` ed eseguire il primo passo di ottimizzazione. **ExploreIR** non modifica la IR ma mostra il suo interno.
```cpp
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
```
Da provare con `$ make alfa`