// Implement an OpenMP program to perform the addition of two one-dimensional arrays of size N using the parallel for directive. Display the resulting array and identify the Thread ID that computes each array element.

#include <stdio.h>
#include <omp.h>

int main()
{
	int N;

	printf("Enter number of elements of array: ");
	scanf("%d", &N);

	int A[N], B[N], C[N];

	printf("A: ");
	for (int i = 0; i < N; i++)
	{
		A[i] = i + 1;
		printf("%d ", A[i]);
	}
	printf("\n");

	printf("B: ");
	for (int i = 0; i < N; i++)
	{
		B[i] = (i + 1) * 10;
		printf("%d ", B[i]);
	}
	printf("\n\n");

#pragma omp parallel for
	for (int i = 0; i < N; i++)
	{
		C[i] = A[i] + B[i];
		printf("Thread %d: C[%d] = %d\n", omp_get_thread_num(), i, C[i]);
	}

	printf("\nC: ");
	for (int i = 0; i < N; i++)
		printf("%d ", C[i]);
	printf("\n");
}