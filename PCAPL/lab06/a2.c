/*
Implement an MPI program to read matrix A of size 5 × 5. It produces a resultant matrix B of size 5 × 5.

- Set all principal diagonal elements of B to 0.
- If an element of B is below the principal diagonal, replace it with the maximum value of the corresponding column of A.
- If an element of B is above the principal diagonal, replace it with the minimum value of the corresponding column of A.
- Produce matrix B using 5 processes.
- Use only collective communication routines except broadcast routine.
*/

#include <stdio.h>
#include <mpi.h>

#define N 5

int main(int argc, char *argv[])
{
    int rank, size;

    int A[N][N];
    int columns[N][N];

    int column[N];
    int B_row[N];
    int B[N][N];

    int min, max;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != N)
    {
        if (rank == 0)
            printf("Run the program using exactly 5 processes.\n");

        MPI_Finalize();
        return 0;
    }

    if (rank == 0)
    {
        printf("Enter the 5 x 5 matrix:\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                scanf("%d", &A[i][j]);
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                columns[i][j] = A[j][i];
        }
    }

    MPI_Scatter(columns, N, MPI_INT, column, N, MPI_INT, 0, MPI_COMM_WORLD);

    min = column[0];
    max = column[0];

    for (int i = 1; i < N; i++)
    {
        if (column[i] < min)
            min = column[i];

        if (column[i] > max)
            max = column[i];
    }

    for (int j = 0; j < N; j++)
    {
        if (j < rank)
            B_row[j] = max;

        else if (j == rank)
            B_row[j] = 0;

        else
            B_row[j] = min;
    }

    MPI_Gather(B_row, N, MPI_INT, B, N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nResultant Matrix B:\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                printf("%d\t", B[i][j]);

            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}