// Implement an MPI program to read a 4x4 matrix and display the following output using four processes.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int matrix[4][4];
    int row[4];
    int result[4];
    int output[4][4];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4)
    {
        if (rank == 0)
            printf("Run the program using exactly 4 processes.\n");

        MPI_Finalize();
        return 0;
    }

    if (rank == 0)
    {
        printf("Enter the elements of the 4 x 4 matrix:\n");

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                scanf("%d", &matrix[i][j]);
            }
        }
    }

    MPI_Scatter(matrix, 4, MPI_INT, row, 4, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scan(row, result, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    MPI_Gather(result, 4, MPI_INT, output, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nOutput Matrix:\n");

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%d\t", output[i][j]);

            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}