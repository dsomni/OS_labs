#include <stdlib.h>
#include <stdio.h>

my_realloc_int(int* array, int new_size){
    if (array == NULL){
        array = (int*) malloc(sizeof(int) * new_size);
    }else if (new_size == 0){
        free(array);
        array = NULL;
    }else{
        int* new_array = (int*) malloc(sizeof(int) * new_size);
        for (int i = 0; i < new_size; i++)
        {
            new_array[i] = array[i];
        }
        free(array);
        array = new_array;
    }
}

// I use previous exercise to demonstrate usage
int main()
{
	// Allows user to specify the original array size, stored in variable n1.
	printf("Enter original array size: ");
	int n1 = 0;
	scanf("%d", &n1);

	//Create a new array of n1 ints
	int *a1 = (int *)malloc(sizeof(int) * n1);
	int i;
	for (i = 0; i < n1; i++)
	{
		//Set each value in a1 to 100
		a1[i] = 100;

		//Print each element out (to make sure things look right)
		printf("%d ", a1[i]);
	}

	//User specifies the new array size, stored in variable n2.
	printf("\nEnter new array size: ");
	int n2 = 0;
	scanf("%d", &n2);

	//Dynamically change the array to size n2
	my_realloc_int(a1, n2);

	for (i = 0; i < n2; i++)
	{
		//Print each element out (to make sure things look right)
		printf("%d ", a1[i]);
	}
	printf("\n");

	//Done with array now, done with program :D
	free(a1);

	return 0;
}
