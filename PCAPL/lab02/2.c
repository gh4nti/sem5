/*
Implement an OpenMP program to read a matrix A of size 5x5 and produce matrix B according to the specified transformation:
- Principal diagonal = 0
- Elements below the diagonal = Maximum value of the corresponding row in A
- Elements above the diagonal = Minimum value of the corresponding row in A

Display both matrices and indicate the Thread ID responsible for processing each row.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 5

int main()
{
	int A[N][N], B[N][N];

	srand(time(NULL));

	printf("A:\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			A[i][j] = rand() % 100;
			printf("%4d", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

#pragma omp parallel for
	for (int i = 0; i < N; i++)
	{
		int tid = omp_get_thread_num();

		int min = A[i][0];
		int max = A[i][0];

		// find min and max
		for (int j = 1; j < N; j++)
		{
			if (A[i][j] < min)
				min = A[i][j];
			if (A[i][j] > max)
				max = A[i][j];
		}

		for (int j = 0; j < N; j++)
		{
			if (i == j)
				B[i][j] = 0;
			else if (i > j)
				B[i][j] = max;
			else
				B[i][j] = min;
		}

		printf("Row %d processed by thread %d\n", i, tid);
	}

	printf("B:\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%4d", B[i][j]);
		printf("\n");
	}
	printf("\n");
}