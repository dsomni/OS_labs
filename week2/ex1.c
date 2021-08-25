#include <stdio.h>

int main(){
    int i;
    float f;
    double d;

    i = __INT_MAX__;
    f = __FLT_MAX__;
    d = __DBL_MAX__;

    printf("Integer = %i\n", i);
    printf("Float = %f\n", f);
    printf("Double = %f\n", d);

    printf("Sizeof integer = %lu\n", sizeof(int));
    printf("Sizeof float = %lu\n", sizeof(float));
    printf("Sizeof double = %lu\n", sizeof(double));

    return 0;
}