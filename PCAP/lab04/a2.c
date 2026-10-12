// Implement an MPI program to read N elements of an array in the master process. Let N processes including the master process check whether the array values are prime or not.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int isPrime(int n);

int main(int argc, char *argv[])
{
    int rank, size;
    int *arr = NULL;
    int n;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        arr = (int *)malloc(size * sizeof(int));

        printf("Enter array elements: ");

        for (int i = 0; i < size; i++)
            scanf("%d", &arr[i]);
    }

    MPI_Scatter(arr, 1, MPI_INT, &n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (isPrime(n))
        printf("Process %d: %d is prime\n", rank, n);
    else
        printf("Process %d: %d is not prime\n", rank, n);

    if (rank == 0)
        free(arr);

    MPI_Finalize();

    return 0;
}

int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}
