// Implement an MPI program to read a value M and N×M number of elements into a 1D array in the root, where N is the total number of processes. Find the square of first M numbers, the cube of next M numbers and so on. Print the results in the root.

#include <stdio.h>
#include <mpi.h>

int power(int base, int exp);

int main(int argc, char *argv[])
{
    int rank, size, M;
    int arr[100], local[100];
    int result[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter M: ");
        scanf("%d", &M);

        printf("Enter %d elements:\n", size * M);

        for (int i = 0; i < size * M; i++)
            scanf("%d", &arr[i]);
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(arr, M, MPI_INT,
                local, M, MPI_INT,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < M; i++)
        local[i] = power(local[i], rank + 2);

    MPI_Gather(local, M, MPI_INT,
               result, M, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Result:\n");

        for (int i = 0; i < size * M; i++)
            printf("%d ", result[i]);

        printf("\n");
    }

    MPI_Finalize();

    return 0;
}

int power(int base, int exp)
{
    int result = 1;

    for (int i = 0; i < exp; i++)
        result *= base;

    return result;
}