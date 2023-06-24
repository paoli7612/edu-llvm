#include <stdio.h>

int foo(int a) {
    int b = a * 2;
    printf("%d", b);
    int c = b * 16;
    printf("%d", c);
    int d = c/2;
    printf("%d", d);
    int e = d * d;
    return e;    
}

int main() {
    int result = foo(10);
    printf("Result: %d\n", result);
    return 0;
}