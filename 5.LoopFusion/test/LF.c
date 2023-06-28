void populate (int a[10], int b[10], int c[10]) {
    int i;

    for(i=0; i<10; i++) {
        a[i] = 5*c[i];
    }

    for(i=0; i<10; i++) {
        b[i] = a[i]+c[i];
    }
}