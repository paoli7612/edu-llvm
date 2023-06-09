#include "LocalOpts.h"

using namespace llvm;

bool eliminateDeadCode(Module &M)
{
    bool modified = false;
    for (Function &F : M) {
        for (Function::iterator BB = F.begin(), E = F.end(); BB != E; ++BB) {
            for (BasicBlock::iterator I = BB->begin(), E = BB->end(); I != E;) {
                Instruction *Inst = &*I;
                ++I;
                if (Inst->use_empty() && !Inst->isTerminator())
                {
                    Inst->eraseFromParent();
                    modified = true;
                }
            }
        }
    }
    return modified;
}

// true se V è un numero intero
bool isInteger(const Value *V)
{
    return V->getType()->isIntegerTy();
}

// true se il valore costante contenuto in V == n
bool isInteger(const Value *V, const int n) {
    if (const ConstantInt *CI = dyn_cast<ConstantInt>(V)) {
        return CI->equalsInt(n);
    }
    return false;
}

/* Ritorna 0 se il primo operando è uno 0*/
/* Ritorna 1 se il secondo operando è uno 0*/
/* Ritorna -1 se nessun'operando è uno 0*/
bool posOperand0(const Instruction &I)
{
    if (isInteger(I.getOperand(0), 0))
        return 0;
    else if (isInteger(I.getOperand(1), 0))
        return 1;
    else
        return -1;
}

/* Ritorna 0 o 1 in base alla posizione di I negli operandi di U */
int posOperand(User *U, Value &V)
{
    return U->getOperand(0) != &V;
}

void performAlgebraicIdentity(Instruction &I, int pos0)
{
    // outs() << "___________________________________\n";
    // I.printAsOperand(outs());
    // outs() << " = ";
    // I.getOperand(0)->printAsOperand(outs());
    // outs() << " + ";
    // I.getOperand(1)->printAsOperand(outs());
    // outs() << "\n";
    //outs() << "___________________________________\n";

    Value *Y = I.getOperand(!pos0);

    outs() << "posso sostituire "; I.printAsOperand(outs());
    outs() << " con "; Y->printAsOperand(outs()); outs() << "\n";

    SmallVector<User *, 4> usersCopy(I.users().begin(), I.users().end());
    for (User *x : usersCopy)
    {
        int pos = posOperand(x, I);
        x->setOperand(pos, Y);
    }
}

void findAlgebraicIdentity(Module &M)
{
    for (Function &F : M) {
        for (BasicBlock &B : F) {
            for (Instruction &I : B) {
                if (I.isBinaryOp()) {
                    if (I.getOpcode() == Instruction::Add) {
                        int pos0 = posOperand0(I);
                        if (pos0 != -1) {
                            outs() << "Trovato: " << I << "\tpos: " << pos0 << "\n";
                            performAlgebraicIdentity(I, pos0);
                        }
                    }
                }
            }
        }
    }
}

void print(Module &M)
{
    for (Function &F : M)
    {
        for (BasicBlock &B : F)
        {
            for (Instruction &I : B)
            {
                outs() << I << "\n";
            }
        }
    }
}

PreservedAnalyses AlgebraicIdentityPass::run([[maybe_unused]] Module &M, ModuleAnalysisManager &)
{
    print(M); // stampo la IR iniziale
    findAlgebraicIdentity(M); // applico la AlgebraicIdentity
    print(M); // stampo la IR modificata
    eliminateDeadCode(M); // applico la DeadCodeElimination
    print(M); // stampo il risultato ifnale
    return PreservedAnalyses::none();
}
