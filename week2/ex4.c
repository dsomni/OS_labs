#include <stdio.h>

void swap(int* a, int* b)
{
    int d = *a;
    *a = *b;
    *b = d;
}

int main()
{
    int a, b;
    printf("Enter a 1st number:\n");
    scanf("%d", &a);
    printf("Enter a 2nd number:\n");
    scanf("%d", &b);

    printf("Before swap:\n");
    printf("a -> %d  b -> %d\n", a, b);

    swap(&a, &b);

    printf("After swap:\n");
    printf("a -> %d  b-> %d\n", a, b);
    return 0;
}
