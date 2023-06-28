int foo() {
    int a[10];
    for (int i=0; i<10; i++)
        a[i] = i*2;
    for (int i=0; i<10; i++) 
        a[i] += 2;
    return a[9];
}