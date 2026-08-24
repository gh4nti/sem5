// Implement an MPI program to read N values in the root process. Root process sends one value to each process. Every process receives it and finds the factorial of that number and returns it to the root process. Root process gathers the factorial and finds the sum of it. Use N number of processes.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int num, fact = 1;
	int values[100], factorials[100];
	int sum = 0;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		printf("Enter %d values: \n", size);
		for (int i = 0; i < size; i++)
			scanf("%d", &values[i]);
	}

	MPI_Scatter(values, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 1; i <= num; i++)
		fact *= i;

	printf("Process %d: %d! = %d\n", rank, num, fact);

	MPI_Gather(&fact, 1, MPI_INT, factorials, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		for (int i = 0; i < size; i++)
			sum += factorials[i];

		printf("Sum of factorials = %d\n", sum);
	}

	MPI_Finalize();

	return 0;
}