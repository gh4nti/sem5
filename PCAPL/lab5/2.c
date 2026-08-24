// Implement an MPI program to read an integer value M and NxM elements into a 1D array in the root process, where N is the number of processes. Root process sends M elements to each process. Each process finds average of M elements it received and sends these average values to root. Root collects all the values and finds the total average. Use collective communication routines.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size, M;
	int arr[100], local[100];
	float local_avg, averages[100];
	float sum = 0, total_avg;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		printf("Enter M: ");
		scanf("%d", &M);
	}

	MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("Enter %d elements:\n", size * M);
		for (int i = 0; i < size * M; i++)
			scanf("%d", &arr[i]);
	}

	MPI_Scatter(arr, M, MPI_INT, local, M, MPI_INT, 0, MPI_COMM_WORLD);
	sum = 0;

	for (int i = 0; i < M; i++)
		sum += local[i];

	local_avg = sum / M;

	printf("Process %d average = %.2f\n", rank, local_avg);

	MPI_Gather(&local_avg, 1, MPI_FLOAT, averages, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		sum = 0;

		for (int i = 0; i < size; i++)
			sum += averages[i];

		total_avg = sum / size;
		printf("Total average = %.2f\n", total_avg);
	}

	MPI_Finalize();

	return 0;
}