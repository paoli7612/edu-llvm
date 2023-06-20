#include <stdio.h>

int foo(int x, int y) {
    int a = x + y;
    int b = a * 2;
    int c = b / 3;
    return c;
}

int main() {
    int result = foo(10, 20);
    printf("Result: %d\n", result);
    return 0;
}