//Nome della funzione: somma
//Numero di Argomenti: 2
//Numero di chiamate: 0
//Numero di BB: 1
//Numero di Istruzioni: 2
int somma(int a, int b) {
  int s = a + b;
  return s;
}

//Nome della funzione: sottrazione
//Numero di Argomenti: 2
//Numero di chiamate: 0
//Numero di BB: 1
//Numero di Istruzioni: 3
int sottrazione(int a, int b) {
  int s = a - b;
  s = s + 10;
  s = s + 2;
  s = s + 0;
  s = somma(s, s);
  return s;
}


int main() {
  return 0;
}