#include <stdio.h>

void swap(int *x, int *y)
{
    int t;
    t = *x;
    *x = *y;
    *y = t;
}

void bubble_sort(int *a, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

int main()
{
    int size;
    printf("Input size of an array:\n");
    scanf("%d", &size);
    int *a;
    printf("\nInput %d integers separated with spaces:\n", size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &a[i]);
    }

    bubble_sort(a, size);

    printf("\nSorted array:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}