// Implement a C program to read a matrix A of size 5x5. It produces a resultant matrix B of size 5x5. It sets all the principal diagonal elements of B matrix with 0. It replaces each row elements in the B matrix in the following manner. If the element is below the principal diagonal it replaces it with the maximum value of the row in the A matrix having the same row number of B. If the element is above the principal diagonal it replaces it with the minimum value of the row in the A matrix having the same row number of B.

#include <stdio.h>
#include <omp.h>

int main()
{
    int A[5][5], B[5][5];
    int min[5], max[5];

    printf("Enter the elements of the 5x5 matrix:\n");
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            scanf("%d", &A[i][j]);

#pragma omp parallel for
    for (int i = 0; i < 5; i++)
    {
        min[i] = A[i][0];
        max[i] = A[i][0];

        for (int j = 1; j < 5; j++)
        {
            if (A[i][j] < min[i])
                min[i] = A[i][j];

            if (A[i][j] > max[i])
                max[i] = A[i][j];
        }
    }

#pragma omp parallel for
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == j)
                B[i][j] = 0;
            else if (i < j)
                B[i][j] = min[i];
            else
                B[i][j] = max[i];
        }

        int tid = omp_get_thread_num();
        printf("Row %d computed by Thread %d\n", i, tid);
    }

    printf("\nA:\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
            printf("%4d", A[i][j]);
        printf("\n");
    }

    printf("\nB:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            printf("%4d", B[i][j]);
        printf("\n");
    }

    return 0;
}