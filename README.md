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
# 1. Test Pass
Il primo esercizio consiste scorrere le funzioni del modulo e stampare le informazioni importanti.
```cpp
// Nome della funzione: g_incr
// Numero di Argomenti: 1
// Numero di chiamate: 0
// Numero di BB: 1
// Numero di Istruzioni: 4
```
Per entrambi i file di input `Loop.c` e `Fibonacci.c` possiamo facilmente provare questo passo usando il makefile
```makefile
Loop: $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/Loop.c -o loop.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=test-pass loop.ll -disable-output

Fibonacci: $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/Fibonacci.c -o Fibonacci.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=test-pass Fibonacci.ll -disable-output
```

Per esempio `$ make Loop` genererà la IR senza ottimizzazioni col comando **clang**. Eseguirà poi l'ottimizzazione della IR generata con il passo creato nella cartella `1.TestPass/lib` chiamato **test-pass**. Questo passo non genererà output (infatti è impostata l'opzione `-disable-output`), ma stamperà il risultato sul stdout.



