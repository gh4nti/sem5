// Implement an OpenMP program that performs the addition of two one-dimensional arrays using the parallel for directive.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    int n;

    printf("Enter array size: ");
    scanf("%d", &n);

    int A[n], B[n], C[n];

    srand(time(NULL));

    for(int i = 0; i < n; i++)
    {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    printf("\nA:\n");
    for(int i = 0; i < n; i++)
        printf("%4d", A[i]);

    printf("\n\nB:\n");
    for(int i = 0; i < n; i++)
        printf("%4d", B[i]);

    printf("\n");

    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        C[i] = A[i] + B[i];
        printf("Element %d computed by Thread %d\n", i, omp_get_thread_num());
    }

    printf("\nResult:\n");
    for(int i = 0; i < n; i++)
        printf("%4d", C[i]);

    printf("\n");

    return 0;
}