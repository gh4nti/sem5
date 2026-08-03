// Implement a parallel program using OpenMP to perform vector addition, subtraction, and multiplication. Demonstrate task level parallelism. Analyze the speedup and efficiency of the parallelized code.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
	int n;

    printf("Enter the size of the vectors: ");
    scanf("%d", &n);

    int A[n], B[n];
    int add[n], sub[n], mul[n];

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    printf("\nA:\n");
    for (int i = 0; i < n; i++)
        printf("%5d", A[i]);

    printf("\n\nB:\n");
    for (int i = 0; i < n; i++)
        printf("%5d", B[i]);

    // serial
    double serial_start = omp_get_wtime();

    for (int i = 0; i < n; i++)
        add[i] = A[i] + B[i];

    for (int i = 0; i < n; i++)
        sub[i] = A[i] - B[i];

    for (int i = 0; i < n; i++)
        mul[i] = A[i] * B[i];

    double serial_end = omp_get_wtime();

    // parallel
    double parallel_start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                int tid = omp_get_thread_num();
                printf("\nAddition performed by thread %d\n", tid);

                for (int i = 0; i < n; i++)
                    add[i] = A[i] + B[i];
            }

            #pragma omp task
            {
                int tid = omp_get_thread_num();
                printf("subtraction performed by thread %d\n", tid);

                for (int i = 0; i < n; i++)
                    sub[i] = A[i] - B[i];
            }

            #pragma omp task
            {
                int tid = omp_get_thread_num();
                printf("Multiplication performed by thread %d\n", tid);

                for (int i = 0; i < n; i++)
                    mul[i] = A[i] * B[i];
            }

            #pragma omp taskwait
        }
    }

    double parallel_end = omp_get_wtime();

    printf("\nAddition Result:\n");
    for (int i = 0; i < n; i++)
        printf("%5d", add[i]);

    printf("\n\nSubtraction Result:\n");
    for (int i = 0; i < n; i++)
        printf("%5d", sub[i]);

    printf("\n\nMultiplication Result:\n");
    for (int i = 0; i < n; i++)
        printf("%5d", mul[i]);

    double serial_time = serial_end - serial_start;
    double parallel_time = parallel_end - parallel_start;

    double speedup = serial_time / parallel_time;
    double efficiency = speedup / omp_get_max_threads();

    printf("\n\nSerial Execution Time: %f seconds", serial_time);
    printf("\nParallel Execution Time: %f seconds", parallel_time);
    printf("\nSpeedup: %f", speedup);
    printf("\nEfficiency: %f\n", efficiency);
}