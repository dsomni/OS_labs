#include <stdio.h>

void printMultipleChars(char chr, int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        printf("%c", chr);
    }
}

void printTriangle(int n)
{
    for (int i = 1, spaces = n; i <= 2 * n - 1; i += 2, spaces--)
    {
        printMultipleChars(' ', spaces);
        printMultipleChars('*', i);
        printMultipleChars(' ', spaces);
        printf("\n");
    }
    printf("\n");
}

void printSemiTriangle(int n)
{
    for (int i = 1; i <= n; i++)
    {
        printMultipleChars('*', i);
        printf("\n");
    }
    printf("\n");
}

void printArrow(int n)
{
    for (int i = 1; i <= n; i++)
    {
        printMultipleChars('*', i);
        printf("\n");
    }
    for (int i = n - 1; i > 0; i--)
    {
        printMultipleChars('*', i);
        printf("\n");
    }
    printf("\n");
}

void printSquare(int n)
{
    for (int i = 0; i < n; i++)
    {
        printMultipleChars('*', n);
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int n;
    sscanf(argv[1], "%d", &n);

    printTriangle(n);
    printSemiTriangle(n);
    printArrow(n);
    printSquare(n);

    return 0;
}
