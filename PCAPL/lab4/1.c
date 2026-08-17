// Implement a simple MPI program to find out pow(x, rank) for all the processes where x is an integer constant and rank is the rank of the process.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, x = 2;
	int result = 1;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for (int i = 0; i < rank; i++)
		result *= x;

	printf("Process %d: %d^%d = %d\n", rank, x, rank, result);

	MPI_Finalize();
	return 0;
}