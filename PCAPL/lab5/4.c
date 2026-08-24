// Implement an MPI Program to read two strings S1 and S2 of same length in the root process. Using N processes including the root (string length is evenly divisible by N), produce the resultant string as shown below. Display the resultant string in the root process. Use Collective communication routines.

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int len, chunk;

    char s1[100], s2[100];
    char local1[100], local2[100];
    char local_result[200];
    char result[200];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter string S1: ");
        scanf("%s", s1);

        printf("Enter string S2: ");
        scanf("%s", s2);

        len = strlen(s1);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    chunk = len / size;

    MPI_Scatter(s1, chunk, MPI_CHAR,
                local1, chunk, MPI_CHAR,
                0, MPI_COMM_WORLD);

    MPI_Scatter(s2, chunk, MPI_CHAR,
                local2, chunk, MPI_CHAR,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++)
    {
        local_result[2 * i] = local1[i];
        local_result[2 * i + 1] = local2[i];
    }

    MPI_Gather(local_result, 2 * chunk, MPI_CHAR,
               result, 2 * chunk, MPI_CHAR,
               0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        result[2 * len] = '\0';

        printf("Resultant String: %s\n", result);
    }

    MPI_Finalize();

    return 0;
}