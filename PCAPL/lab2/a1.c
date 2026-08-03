// Implement an OpenMP program to calculate pow(i, x), where i is an integer entered by the user and x is the Thread ID.

#include <stdio.h>
#include <math.h>
#include <omp.h>

int main()
{
    int i;

    printf("Enter an integer: ");
    scanf("%d", &i);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        double result = pow(i, tid);

        printf("Thread %d: %d^%d = %.2f\n", tid, i, tid, result);
    }

    return 0;
}