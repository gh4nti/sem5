// Implement a C program that reads a character type matrix and integer type matrix B of size MxN. It produces and output string STR such that, every character of A is repeated r times (where r is the integer value in matrix B which is having the same index as that of the character taken in A).

#include <stdio.h>
#include <omp.h>

int main()
{
    int M, N;

    printf("Enter number of rows and columns: ");
    scanf("%d%d", &M, &N);

    char A[M][N];
    int B[M][N];

    printf("Enter the character matrix:\n");
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf(" %c", &A[i][j]);

    printf("Enter the integer matrix:\n");
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &B[i][j]);

    printf("\nOutput String: ");

#pragma omp parallel for ordered
    for (int i = 0; i < M; i++)
    {
#pragma omp ordered
        {
            for (int j = 0; j < N; j++)
                for (int k = 0; k < B[i][j]; k++)
                    printf("%c", A[i][j]);
        }
    }
    printf("\n");

    return 0;
}