// Implement an MPI program to read an integer value in the root process. Root process sends this value to Process1, Process1 sends this value to Process2 and so on. The last process sends the value back to the root process. When sending the value each process will first increment the received value by one. Implement the program using point-to-point communication routines.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size, n;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		printf("Enter an integer: ");
		scanf("%d", &n);

		n++;

		MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&n, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("Final value received: %d\n", n);
	}
	else
	{
		MPI_Recv(&n, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("Process %d received %d\n", rank, n);

		n++;

		if (rank == size - 1)
			MPI_Send(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		else
			MPI_Send(&n, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}