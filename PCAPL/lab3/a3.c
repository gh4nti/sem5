/*
Implement an OpenMP program to compute the factorial of N numbers using:
- critical section
- atomic
- reduction
- master
- locks

Compare the execution time of each synchronization construct.
*/

#include <stdio.h>
#include <omp.h>

int main()
{
    int N, threads;
    unsigned long long factorial;
    double start, end;

    printf("Enter N: ");
    scanf("%d", &N);

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    // critical section
    factorial = 1;

    start = omp_get_wtime();

#pragma omp parallel for
    for (int i = 1; i <= N; i++)
    {
#pragma omp critical
        {
            factorial *= i;
        }
    }

    end = omp_get_wtime();

    printf("\nUsing Critical Section:\n");
    printf("Factorial = %llu\n", factorial);
    printf("Execution time = %f seconds\n", end - start);

    // atomic
    factorial = 1;

    start = omp_get_wtime();

#pragma omp parallel
    {
        unsigned long long local_product = 1;

#pragma omp for
        for (int i = 1; i <= N; i++)
            local_product *= i;

#pragma omp atomic
        factorial *= local_product;
    }

    end = omp_get_wtime();

    printf("\nUsing Atomic:\n");
    printf("Factorial = %llu\n", factorial);
    printf("Execution time = %f seconds\n", end - start);

    // reduction
    factorial = 1;

    start = omp_get_wtime();

#pragma omp parallel for reduction(* : factorial)
    for (int i = 1; i <= N; i++)
        factorial *= i;

    end = omp_get_wtime();

    printf("\nUsing Reduction:\n");
    printf("Factorial = %llu\n", factorial);
    printf("Execution time = %f seconds\n", end - start);

    // master
    factorial = 1;

    start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp master
        {
            for (int i = 1; i <= N; i++)
                factorial *= i;
        }
    }

    end = omp_get_wtime();

    printf("\nUsing Master:\n");
    printf("Factorial = %llu\n", factorial);
    printf("Execution time = %f seconds\n", end - start);

    // lock
    factorial = 1;

    omp_lock_t lock;
    omp_init_lock(&lock);

    start = omp_get_wtime();

#pragma omp parallel for
    for (int i = 1; i <= N; i++)
    {
        omp_set_lock(&lock);

        factorial *= i;

        omp_unset_lock(&lock);
    }

    end = omp_get_wtime();

    printf("\nUsing Locks:\n");
    printf("Factorial = %llu\n", factorial);
    printf("Execution time = %f seconds\n", end - start);

    omp_destroy_lock(&lock);

    return 0;
}