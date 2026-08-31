// Implement an MPI program to read a word of length N. Using N processes including the root, obtain an output word with the pattern shown in the example. Display the resultant output word in the root process.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char word[100];
    char ch;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter a word of length %d: ", size);
        scanf("%s", word);

        if (strlen(word) != size)
        {
            printf("Word length must be equal to number of processes.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Scatter(word, 1, MPI_CHAR, &ch, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    int count = rank + 1;

    char *local = (char *)malloc(count * sizeof(char));

    for (int i = 0; i < count; i++)
        local[i] = ch;

    int *recvcounts = NULL;
    int *displs = NULL;
    char *result = NULL;

    if (rank == 0)
    {
        recvcounts = (int *)malloc(size * sizeof(int));
        displs = (int *)malloc(size * sizeof(int));

        int total = 0;

        for (int i = 0; i < size; i++)
        {
            recvcounts[i] = i + 1;
            displs[i] = total;
            total += i + 1;
        }

        result = (char *)malloc((total + 1) * sizeof(char));
        result[total] = '\0';
    }

    MPI_Gatherv(local, count, MPI_CHAR, result, recvcounts, displs, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Output word: %s\n", result);

        free(recvcounts);
        free(displs);
        free(result);
    }

    free(local);

    MPI_Finalize();
    return 0;
}