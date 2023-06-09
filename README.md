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

# 2. LocalOpts
## 2.1 Algebraic Identity
Il primo compito consiste nell'implementare un passo LLVM che esegue l'ottimizzazione locale **algebraic identity**. Nel file `2.LocalOpts/lib/AlgebraicIdentity.cpp` si trova il passo che viene incluso dal file di configurazione dei passi `2.LocalOpts/lib/LocalOpts.cpp`.

Tale passo ora è in grado di trovare le istruzioni che comprendono una somma con un'operando a 0. Una volta trovata l'istruzione va a scorrere tutti gli usi del nome di quell'istruzione per andare a sostituire con l'addendo che non è 0. Una volta finito possiamo avviare la **dead code elimination** per rimuovere le righe diventate **dead code**.

Per rendere più "verboso" il passaggio:
```cpp
    print(M); // stampo la IR iniziale
    findAlgebraicIdentity(M); // applico la AlgebraicIdentity
    print(M); // stampo la IR modificata
    eliminateDeadCode(M); // applico la DeadCodeElimination
    print(M); // stampo il risultato ifnale
```

Inolte è stato creato un file c `2.LocalOpts/test/hello-world.c` e una regola nel makefile per provare questo passo. `$ make hello-world`. Notiamo però che dopo aver "migliorato" la IR con questo passo è stata eliminata anche la funzionalità del printf (non ho considerato i **side effect**). Quindi è stata considerata **DeadCode** ed eliminata pure la stampa su stdout.
