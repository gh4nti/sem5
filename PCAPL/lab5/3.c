// Implement an MPI program to read a string. Using N processes (string length is evenly divisible by N), find the number of non-vowels in the string. In the root process print number of non-vowels found by each process and print the total number of non-vowels.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	char str[100], local[100];
	int len, chunk;
	int local_count = 0;
	int counts[100];
	int total = 0;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		printf("Enter a string: ");
		fgets(str, 100, stdin);

		str[strcspn(str, "\n")] = 0;

		len = strlen(str);
	}

	MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

	chunk = len / size;

	MPI_Scatter(str, chunk, MPI_CHAR, local, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);

	for (int i = 0; i < chunk; i++)
    {
        char ch = tolower(local[i]);

        if (ch != 'a' && ch != 'e' && ch != 'i' &&
            ch != 'o' && ch != 'u')
            local_count++;
    }

    MPI_Gather(&local_count, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            printf("Process %d: Number of non-vowels = %d\n",
                   i, counts[i]);

            total += counts[i];
        }

        printf("Total number of non-vowels = %d\n", total);
    }

    MPI_Finalize();

    return 0;

}