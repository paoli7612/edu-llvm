int g;
// Nome della funzione: g_incr
// Numero di Argomenti: 1
// Numero di chiamate: 0
// Numero di BB: 1
// Numero di Istruzioni: 4

int g_incr(int c) {
  g += c;
  return g;
}

// Nome della funzione: loop
// Numero di Argomenti: 3
// Numero di chiamate: 0
// Numero di BB: 3
// Numero di Istruzioni: 10
int loop(int a, int b, int c) {
  int i, ret = 0;

  for (i = a; i < b; i++) {
    g_incr(c);
  }

  return ret + g;
}
