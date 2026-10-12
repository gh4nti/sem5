// Implement an OpenMP program to perform matrix-vector multiplication. Record the effect of increasing matrix size on execution time.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
	int M, N;

	printf("Enter no. of rows (M) and columns (N): ");
	scanf("%d%d", &M, &N);

	int A[M][N], X[N], Ys[M], Yp[M];

	srand(time(NULL));

	printf("A:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			A[i][j] = rand() % 100;
			printf("%4d", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("X:\n");
	for (int i = 0; i < N; i++)
	{
		X[i] = rand() % 100;
		printf("%5d", X[i]);
	}
	printf("\n");

	// serial multiplication
	double serial_start = omp_get_wtime();

	for (int i = 0; i < M; i++)
	{
		Ys[i] = 0;
		for (int j = 0; j < N; j++)
			Ys[i] += A[i][j] * X[j];
	}

	double serial_end = omp_get_wtime();

	// parallel multiplication
	double parallel_start = omp_get_wtime();

#pragma omp parallel for
	for (int i = 0; i < M; i++)
	{
		int tid = omp_get_thread_num();

		Yp[i] = 0;
		for (int j = 0; j < N; j++)
			Yp[i] += A[i][j] * X[j];

		printf("Row %d computed by thread %d\n", i, tid);
	}

	double parallel_end = omp_get_wtime();

	printf("\nResult Vector:\n");
	for (int i = 0; i < M; i++)
		printf("%8d", Yp[i]);
	printf("\n");

	printf("\nSerial Execution Time: %f seconds\n", serial_end - serial_start);
	printf("Parallel Execution Time: %f seconds\n", parallel_end - parallel_start);

	return 0;
}