#include <stdio.h>
#undef bool
#include "qglobal.h"

int main(int argc, char *argv[]) {
    printf("void* = %d\n", sizeof(void *));
    printf("bool = %d\n", sizeof(bool));
    printf("char = %d\n", sizeof(char));
    printf("short = %d\n", sizeof(short));
    printf("int = %d\n", sizeof(int));
    printf("long = %d\n", sizeof(long));
    printf("float = %d\n", sizeof(float));
    printf("double = %d\n", sizeof(double));
    printf("long double = %d\n", sizeof(long double));
    return 0;
}
