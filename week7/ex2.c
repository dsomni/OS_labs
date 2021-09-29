#include <stdio.h>
#include <stdlib.h>

void fill_array(int *array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        array[i] = i;
    }
}

void print_array(int *array, int array_size)
{
    printf("Array: ");
    for (int i = 0; i < array_size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{
    int array_size;
    printf("Enter size of array: ");
    scanf("%d", &array_size);
    printf("\n");

    printf("Memory has been allocated\n");
    int *array = (int *)malloc(sizeof(int) * array_size);
    fill_array(array, array_size);
    print_array(array, array_size);

    free(array);
    printf("Memory has been deallocated\n");

    return 0;
}