// Implement a C program to perform Matrix times vector product operation.

#include <stdio.h>
#include <omp.h>

int main()
{
    int M, N;

    printf("Enter the number of rows (M): ");
    scanf("%d", &M);

    printf("Enter the number of columns (N): ");
    scanf("%d", &N);

    int arr[M][N], vec[N], res[M];

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &arr[i][j]);

    printf("Enter the vector elements:\n");
    for (int i = 0; i < N; i++)
        scanf("%d", &vec[i]);

#pragma omp parallel for
    for (int i = 0; i < M; i++)
    {
        res[i] = 0;
        for (int j = 0; j < N; j++)
            res[i] += arr[i][j] * vec[j];

        int tid = omp_get_thread_num();
        printf("Row %d computed by Thread %d\n", i, tid);
    }

    printf("\nResultant Vector:\n");
    for (int i = 0; i < M; i++)
        printf("%d ", res[i]);
    printf("\n");
    return 0;
}