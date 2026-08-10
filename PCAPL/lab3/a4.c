/*
Implement a parallel OpenMP program to estimate the value of π using the Monte Carlo (Random Shooting) technique.

Hint:
- randomly generate points inside the square [0,1] x [0,1].
- count the number of points inside the quarter circle.

Estimate π using:
π = 4 x Total number of generated points / Number of points inside the circle

Compare the execution time for different numbers of threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

unsigned int random_number(unsigned int *seed);

int main()
{
    long long N;
    int threads;
    double start, end;

    printf("Enter number of random points: ");
    scanf("%lld", &N);

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    long long inside_circle = 0;

    start = omp_get_wtime();

#pragma omp parallel
    {
        unsigned int seed = 1234 + omp_get_thread_num();
        long long local_count = 0;

#pragma omp for
        for (long long i = 0; i < N; i++)
        {
            double x = (double)random_number(&seed) / 32767.0;
            double y = (double)random_number(&seed) / 32767.0;

            if (x * x + y * y <= 1.0)
                local_count++;
        }

#pragma omp atomic
        inside_circle += local_count;
    }

    end = omp_get_wtime();

    double pi = 4.0 * inside_circle / N;
    double execution_time = end - start;

    printf("\n----Monte Carlo Pi Estimation----\n");
    printf("Total points: %lld\n", N);
    printf("Threads: %d\n", threads);
    printf("Points in circle: %lld\n", inside_circle);
    printf("Estimated pi: %.10f\n", pi);
    printf("Execution time: %.6f seconds\n", execution_time);

    return 0;
}

unsigned int random_number(unsigned int *seed)
{
    *seed = (*seed * 1103515245 + 12345);
    return (*seed / 65536) % 32768;
}