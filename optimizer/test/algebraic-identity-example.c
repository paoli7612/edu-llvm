
int foo() {

    int a = 10;
    int b = 20;

    a = a + 0;
    b = b * 1;
    b = 1 * b;
    a = 0 + a;

    return a + b;
}