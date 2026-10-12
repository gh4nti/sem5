// Implement an OpenMP program to compute the sum of elements of a large array in parallel using the parallel for directive. Measure and display the execution time of the parallel program using the omp_get_wtime() runtime function and compare it with the corresponding serial implementation.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
	int N;
	long long serial_sum = 0, parallel_sum = 0;
	double serial_time, parallel_time;

	printf("Enter size of array: ");
	scanf("%d", &N);

	int *arr = (int *)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		arr[i] = 1;

	serial_time = omp_get_wtime();

	for (int i = 0; i < N; i++)
		serial_sum += arr[i];

	serial_time = omp_get_wtime() - serial_time;
	parallel_time = omp_get_wtime();

	#pragma omp parallel for reduction(+:parallel_sum)
	for (int i = 0; i < N; i++)
		parallel_sum += arr[i];

	parallel_time = omp_get_wtime() - parallel_time;

	printf("\nSerial sum: %lld\n", serial_sum);
	printf("Parallel sum: %lld\n", parallel_sum);

	printf("\nSerial execution time: %f sec\n", serial_time);
	printf("Parallel execution time: %f sec\n", parallel_time);

	if (parallel_time > 0)
		printf("Speedup = %f\n", serial_time / parallel_time);

	free(arr);
	return 0;
}