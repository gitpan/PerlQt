#include <pqt.h>

int main(int, char **) {
    PerlIO_printf(PerlIO_stdout(), "IV = %d\n", sizeof(IV));
    PerlIO_printf(PerlIO_stdout(), "void* = %d\n", sizeof(void *));
    PerlIO_printf(PerlIO_stdout(), "bool = %d\n", sizeof(bool));
    PerlIO_printf(PerlIO_stdout(), "char = %d\n", sizeof(char));
    PerlIO_printf(PerlIO_stdout(), "short = %d\n", sizeof(short));
    PerlIO_printf(PerlIO_stdout(), "int = %d\n", sizeof(int));
    PerlIO_printf(PerlIO_stdout(), "long = %d\n", sizeof(long));
    PerlIO_printf(PerlIO_stdout(), "float = %d\n", sizeof(float));
    PerlIO_printf(PerlIO_stdout(), "double = %d\n", sizeof(double));
    PerlIO_printf(PerlIO_stdout(), "long double = %d\n", sizeof(long double));

    return 0;
}
