/*
Write a parallel program using OpenMP to implement the Merge Sort algorithm.

Analyze the performance by computing:
- sequential execution time
- parallel execution time
- speedup
- efficiency

for varying input sizes and thread counts.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int *arr, int left, int mid, int right);
void mergeSort(int *arr, int left, int right);
void mergeSortParallel(int *arr, int left, int right, int depth);

int main()
{
	int n, threads;
	double start, end;

	printf("Enter array size: ");
	scanf("%d", &n);

	printf("Enter no. of threads: ");
	scanf("%d", &threads);

	int *arr = (int *)malloc(n * sizeof(int));
	int *parr = (int *)malloc(n * sizeof(int));

	// random array
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100000;
		parr[i] = arr[i];
	}

	// sequential merge sort
	start = omp_get_wtime();
	mergeSort(arr, 0, n - 1);
	end = omp_get_wtime();
	double st = end - start; // sequential time

	// parallel merge sort
	omp_set_num_threads(threads);
	int depth = 0, temp = threads;

	while (temp > 1)
	{
		depth++;
		temp /= 2;
	}

	start = omp_get_wtime();
	mergeSortParallel(parr, 0, n - 1, depth);
	end = omp_get_wtime();
	double pt = end - start; // parallel time

	double speedup = st / pt;
	double efficiency = speedup / threads;

	printf("\n----PERFORMANCE ANALYSIS----\n");
	printf("Input size: %d\n", n);
	printf("No. of threads: %d\n", threads);
	printf("Sequential time: %f sec\n", st);
	printf("Parallel time: %f sec\n", pt);
	printf("Speedup: %f\n", speedup);
	printf("Efficiency: %f\n", efficiency);

	free(arr);
	free(parr);

	return 0;
}

void merge(int *arr, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *L = (int *)malloc(n1 * sizeof(int));
	int *R = (int *)malloc(n2 * sizeof(int));

	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];

	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + j + 1];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	while (i < n1)
		arr[k++] = L[i++];

	while (j < n2)
		arr[k++] = R[j++];

	free(L);
	free(R);
}

void mergeSort(int *arr, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

void mergeSortParallel(int *arr, int left, int right, int depth)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		if (depth > 0)
		{
#pragma omp parallel sections
			{
#pragma omp section
				mergeSortParallel(arr, left, mid, depth - 1);

#pragma omp section
				mergeSortParallel(arr, mid + 1, right, depth - 1);
			}
		}
		else
		{
			mergeSort(arr, left, mid);
			mergeSort(arr, mid + 1, right);
		}

		merge(arr, left, mid, right);
	}
}