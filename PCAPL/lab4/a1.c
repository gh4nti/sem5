/*
Implement a program in MPI to reverse the digits of the following integer array of size 9 with 9 processes. Initialize the array to the following values.

Input array:
18, 523, 301, 1234, 2, 14, 108, 150, 1928

Output array:
81, 325, 103, 4321, 2, 41, 801, 51, 8291
*/

#include <stdio.h>
#include <mpi.h>

int reverse(int n);

int main(int argc, char *argv[])
{
    int rank, size;
    int arr[9] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 9)
    {
        if (rank == 0)
            printf("Run the program with 9 processes.\n");

        MPI_Finalize();
        return 0;
    }

    arr[rank] = reverse(arr[rank]);

    printf("Process %d: Reversed value = %d\n", rank, arr[rank]);

    MPI_Finalize();

    return 0;
}

int reverse(int n)
{
    int rev = 0;

    while (n != 0)
    {
        rev = rev * 10 + n % 10;
        n = n / 10;
    }

    return rev;
}