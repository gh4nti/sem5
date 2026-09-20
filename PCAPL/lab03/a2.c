// Implement a parallel OpenMP program to generate the histogram of a given array. Compare the execution time of the sequential and parallel implementations.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_VALUE 10

int main()
{
    int N, threads;
    double start, end;

    printf("Enter array size: ");
    scanf("%d", &N);

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    int *arr = malloc(N * sizeof(int));

    int hist_seq[MAX_VALUE + 1] = {0};
    int hist_par[MAX_VALUE + 1] = {0};

    printf("\nArray: ");
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % (MAX_VALUE + 1);
        printf("%d ", arr[i]);
    }

    printf("\n");

    // sequential histogram
    start = omp_get_wtime();

    for (int i = 0; i < N; i++)
        hist_seq[arr[i]]++;

    end = omp_get_wtime();

    double sequential_time = end - start;

    // Parallel Histogram
    omp_set_num_threads(threads);

    start = omp_get_wtime();

#pragma omp parallel
    {
        int local_hist[MAX_VALUE + 1] = {0};

#pragma omp for
        for (int i = 0; i < N; i++)
            local_hist[arr[i]]++;

#pragma omp critical
        {
            for (int i = 0; i <= MAX_VALUE; i++)
                hist_par[i] += local_hist[i];
        }
    }

    end = omp_get_wtime();

    double parallel_time = end - start;

    printf("\nSequential Histogram:\n");
    for (int i = 0; i <= MAX_VALUE; i++)
        printf("%d: %d\n", i, hist_seq[i]);

    printf("\nParallel Histogram:\n");
    for (int i = 0; i <= MAX_VALUE; i++)
        printf("%d: %d\n", i, hist_par[i]);

    printf("\n---- PERFORMANCE ANALYSIS ----\n");
    printf("Sequential execution time: %f sec\n", sequential_time);
    printf("Parallel execution time: %f seconds\n", parallel_time);
    printf("Speedup: %f\n", sequential_time / parallel_time);

    free(arr);

    return 0;
}