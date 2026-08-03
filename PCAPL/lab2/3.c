/*
Implement an OpenMP program that reads a matrix of size MxN and produces:
- Matrix B, where all non-border elements are replaced by their 1's complement.
- Matrix D, where all non-border elements are replaced by the number of set bits (1's) in their binary representation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int countSetBits(int n);

int main()
{
	int M, N;

	printf("Enter no. of rows (M) and columns (N): ");
	scanf("%d%d", &M, &N);

	int A[M][N], B[M][N], D[M][N];

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
	for (int i = 0; i < M; i++)
	{
		int tid = omp_get_thread_num();

		for (int j = 0; j < N; j++)
		{
			if (i == 0 || i == M - 1 || j == 0 || j == N - 1)
			{
				B[i][j] = A[i][j];
				D[i][j] = A[i][j];
			}
			else
			{
				B[i][j] = ~A[i][j];
				D[i][j] = countSetBits(A[i][j]);
			}
		}

		printf("Row %d processed by thread %d\n", i, tid);
	}

	printf("\nB:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%5d", B[i][j]);
		printf("\n");
	}

	printf("\nD:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%5d", D[i][j]);
		printf("\n");
	}
}

int countSetBits(int n)
{
	int c = 0;

	while (n > 0)
	{
		c += n & 1;
		n >>= 1;
	}
	return c;
}