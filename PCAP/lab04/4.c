// Implement an MPI program using synchronous send. The sender process sends a word to the receiver. The second process receives the word, toggles each letter of the word and sends it back to the first process. Both processes use synchronous send operations.

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    char word[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Enter a word: ");
        fgets(word, 100, stdin);

        word[strcspn(word, "\n")] = '\0';

        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(word, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Toggled word received: %s\n", word);
    }
    else if (rank == 1)
    {
        MPI_Recv(word, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; word[i] != '\0'; i++)
        {
            if (word[i] >= 'A' && word[i] <= 'Z')
                word[i] += 32;

            else if (word[i] >= 'a' && word[i] <= 'z')
                word[i] -= 32;
        }

        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}