// Implement an MPI program to read N elements of the array in the root process (process 0) where N is equal to the total number of processes. The root process sends one value to each of the slaves. Let even ranked processes find the square of the received element and odd ranked processes find the cube of the received element. Use Buffered send.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int *arr;
	int n;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		arr = (int *)malloc(size * sizeof(int));
		
		printf("Enter elements of array: ");
		for (int i = 0; i < size; i++)
			scanf("%d", &arr[i]);

		int bufferSize = size * (sizeof(int) + MPI_BSEND_OVERHEAD);
		void *buffer = malloc(bufferSize);

		MPI_Buffer_attach(buffer, bufferSize);

		for (int i = 1; i < size; i++)
			MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);

		MPI_Buffer_detach(&buffer, &bufferSize);

		printf("Process 0: %d^2 = %d\n", arr[0], arr[0] * arr[0]);

		free(buffer);
		free(arr);
	}

	else
	{
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		if (rank % 2 == 0)
			printf("Process %d: %d^2 = %d\n", rank, n, n * n);
		else
			printf("Process %d: %d^3 = %d\n", rank, n, n * n * n);
	}

	MPI_Finalize();
	return 0;
}