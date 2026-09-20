// Implement parallel selection sort.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void selectionSort(int *arr, int n);
void merge(int *arr, int left, int mid, int right);

int main(int argc, char *argv[])
{
    int rank, size, n, local_n;
    int arr[100], local[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter number of elements: ");
        scanf("%d", &n);

        printf("Enter %d elements:\n", n);

        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_n = n / size;

    MPI_Scatter(arr, local_n, MPI_INT,
                local, local_n, MPI_INT,
                0, MPI_COMM_WORLD);

    selectionSort(local, local_n);

    printf("Process %d sorted subarray: ", rank);
    for (int i = 0; i < local_n; i++)
        printf("%d ", local[i]);
    printf("\n");

    MPI_Gather(local, local_n, MPI_INT,
               arr, local_n, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        int currentSize = local_n;

        while (currentSize < n)
        {
            for (int left = 0; left < n - currentSize;
                 left += 2 * currentSize)
            {
                int mid = left + currentSize - 1;
                int right = left + 2 * currentSize - 1;

                if (right >= n)
                    right = n - 1;

                merge(arr, left, mid, right);
            }

            currentSize *= 2;
        }

        printf("Sorted array: ");

        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);

        printf("\n");
    }

    MPI_Finalize();

    return 0;
}

void selectionSort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }

        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void merge(int *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}