// Implement an OpenMP program using the parallel for work-sharing construct to perform the addition of two matrices of size MxN. Display the resultant matrix and the Thread ID responsible for computing each row. Compare the execution time of the serial and parallel implementations and comment on the distribution of loop iterations among the threads.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
	int M, N;

	printf("Enter no. of rows (M) and columns (N): ");
	scanf("%d%d", &M, &N);

	int A[M][N], B[M][N], Cs[M][N], Cp[M][N];

	srand(time(NULL));

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			A[i][j] = rand() % 100;
			B[i][j] = rand() % 100;
		}
	}

	printf("\nA:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%4d", A[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("\nB:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%4d", B[i][j]);
		printf("\n");
	}
	printf("\n");

	// serial addition
	double serial_start = omp_get_wtime();

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			Cs[i][j] = A[i][j] + B[i][j];

	double serial_end = omp_get_wtime();

	// parallel addition
	double parallel_start = omp_get_wtime();

	#pragma omp parallel for
	for (int i = 0; i < M; i++)
	{
		int tid = omp_get_thread_num();

		for (int j = 0; j < N; j++)
			Cp[i][j] = A[i][j] + B[i][j];

		printf("Row %d computed by thread %d\n", i, tid);
	}

	double parallel_end = omp_get_wtime();

	printf("\nAdded matrix:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%4d", Cp[i][j]);
		printf("\n");
	}

	printf("Serial execution time: %f seconds\n", serial_end - serial_start);
	printf("Parallel execution time: %f seconds\n", parallel_end - parallel_start);

	return 0;
}