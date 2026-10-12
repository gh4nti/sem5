// Implement an OpenMP program to perform the addition of two matrices of size M×N using the parallel for directive. Display the resultant matrix and indicate the Thread ID responsible for computing each row (or element) of the result.

#include <stdio.h>
#include <omp.h>

int main()
{
	int M, N;

	printf("Enter the number of rows (M): ");
	scanf("%d", &M);

	printf("Enter the number of columns (N): ");
	scanf("%d", &N);

	int A[M][N], B[M][N], C[M][N];

	printf("A:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			A[i][j] = i + j;
			printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("B:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			B[i][j] = (i + 1) * (j + 1);
			printf("%3d ", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	#pragma omp parallel for
	for (int i = 0; i < M; i++)
	{
		int tid = omp_get_thread_num();
		for (int j = 0; j < N; j++)
			C[i][j] = A[i][j] + B[i][j];

		printf("Row %d computed by %d\n", i, tid);
	}

	printf("\nC:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%3d ", C[i][j]);
		printf("\n");
	}
}