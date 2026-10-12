// Implement a C program that reads a matrix of size MxN and produce an output matrix B of same size such that it replaces all the non-border elements of A with its equivalent 1's complement and remaining elements same as matrix A. Also produce a matrix D as shown below.

#include <stdio.h>
#include <omp.h>

int countSetBits(int n);

int main()
{
    int M, N;

    printf("Enter number of rows and columns: ");
    scanf("%d%d", &M, &N);

    int A[M][N], B[M][N], D[M][N];

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &A[i][j]);

#pragma omp parallel for
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == 0 || i == M - 1 || j == 0 || j == N - 1)
            {
                B[i][j] = A[i][j];
                D[i][j] = A[i][j];
            }
            else
            {
                B[i][j] = ~A[i][j];
                D[i][j] = countSetBits(A[i][j]);
            }
        }

        int tid = omp_get_thread_num();
        printf("Row %d processed by Thread %d\n", i, tid);
    }

    printf("\nA:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%4d", A[i][j]);
        printf("\n");
    }

    printf("\nB:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%4d", B[i][j]);
        printf("\n");
    }

    printf("\nD:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%4d", D[i][j]);
        printf("\n");
    }

    return 0;
}

int countSetBits(int n)
{
    int count = 0;

    while (n > 0)
    {
        count += n & 1;
        n >>= 1;
    }

    return count;
}