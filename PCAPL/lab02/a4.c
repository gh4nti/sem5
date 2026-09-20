// Implement an OpenMP program to generate prime numbers within a user-specified interval using the parallel for directive.

#include <stdio.h>
#include <math.h>
#include <omp.h>

int isPrime(int n);

int main()
{
    int start, end;

    printf("Enter starting number: ");
    scanf("%d", &start);

    printf("Enter ending number: ");
    scanf("%d", &end);

    printf("\nPrime Numbers:\n");

#pragma omp parallel for
    for (int i = start; i <= end; i++)
    {
        if (isPrime(i))
        {
            printf("%d (Thread %d)\n",
                   i, omp_get_thread_num());
        }
    }

    return 0;
}

int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;

    return 1;
}