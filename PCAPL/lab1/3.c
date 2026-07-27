// Implement an OpenMP program to initialize all elements of a 5 × 5 matrix with consecutive integers inside a parallel region using the parallel directive. Display the initialized matrix and print the Thread ID responsible for initializing each row.

#include <stdio.h>
#include <omp.h>

int main()
{
	int arr[5][5];

#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < 5; i++)
		{
			int tid = omp_get_thread_num();

			for (int j = 0; j < 5; j++)
				arr[i][j] = i * 5 + j + 1;

			printf("%d initialized by thread ID: %d\n", i, tid);
		}
	}

	printf("Matrix:\n");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			printf("%3d ", arr[i][j]);
		printf("\n");
	}

	return 0;
}