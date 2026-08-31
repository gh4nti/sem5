// Implement an MPI program using N processes to find 1! + 2! + ... + N! Use MPI_Scan. Also, handle different errors using error-handling routines.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

long long factorial(int n);

int main(int argc, char *argv[])
{
	int rank, size, err;
	long long fact, partialSum;

	err = MPI_Init(&argc, &argv);

	if (err != MPI_SUCCESS)
	{
		printf("Error initializing MPI.\n");
		return 1;
	}

	MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

	err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (err != MPI_SUCCESS)
	{
		printf("Error getting no. of processes.\n");
		MPI_Abort(MPI_COMM_WORLD, err);
	}

	fact = factorial(rank + 1);

	err = MPI_Scan(&fact, &partialSum, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

	if (err != MPI_SUCCESS)
    {
        char error_string[MPI_MAX_ERROR_STRING];
        int length;

        MPI_Error_string(err, error_string, &length);

        printf("Process %d: MPI_Scan error: %s\n",
               rank, error_string);

        MPI_Abort(MPI_COMM_WORLD, err);
    }

    printf("Process %d: %d! = %lld, Partial Sum = %lld\n", rank, rank + 1, fact, partialSum);

    if (rank == size - 1)
        printf("\nFinal Sum = 1! + 2! + ... + %d! = %lld\n", size, partialSum);

    MPI_Finalize();
    return 0;
}

long long factorial(int n)
{
    long long fact = 1;

    for (int i = 1; i <= n; i++)
        fact *= i;

    return fact;
}