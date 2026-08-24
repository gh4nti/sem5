// Implement an MPI program using collective communication functions, to replace all even elements of array A with 1 and replace all odd elements with 0, for an array of size N. Display the resultant array A, count of all even and odd numbers in the root process. Assume N is evenly divisible by the number of processes.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int N, local_n;

    int A[100];
    int local[100];

    int local_even = 0, local_odd = 0;
    int total_even = 0, total_odd = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter size N: ");
        scanf("%d", &N);

        printf("Enter %d elements:\n", N);

        for (int i = 0; i < N; i++)
            scanf("%d", &A[i]);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_n = N / size;

    MPI_Scatter(A, local_n, MPI_INT,
                local, local_n, MPI_INT,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < local_n; i++)
    {
        if (local[i] % 2 == 0)
        {
            local[i] = 1;
            local_even++;
        }
        else
        {
            local[i] = 0;
            local_odd++;
        }
    }

    MPI_Gather(local, local_n, MPI_INT,
               A, local_n, MPI_INT,
               0, MPI_COMM_WORLD);

    MPI_Reduce(&local_even, &total_even, 1,
               MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_odd, &total_odd, 1,
               MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Resultant Array (A): ");

        for (int i = 0; i < N; i++)
            printf("%d ", A[i]);

        printf("\nEven (Count) = %d\n", total_even);
        printf("Odd (Count) = %d\n", total_odd);
    }

    MPI_Finalize();

    return 0;
}