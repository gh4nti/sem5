// Write a CUDA program to perform Sparse Matrix-Vector Multiplication using the Compressed Sparse Row (CSR) representation.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void sparseMatVec(int *data, int *col_index,
                             int *row_ptr, int *x, int *y,
                             int rows) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rows) {
        int sum = 0;

        for (int j = row_ptr[row]; j < row_ptr[row + 1]; j++)
            sum += data[j] * x[col_index[j]];

        y[row] = sum;
    }
}

int main() {
    int rows, cols, nnz;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter number of non-zero elements: ");
    scanf("%d", &nnz);

    int *data = (int *)malloc(nnz * sizeof(int));
    int *col_index = (int *)malloc(nnz * sizeof(int));
    int *row_ptr = (int *)malloc((rows + 1) * sizeof(int));
    int *x = (int *)malloc(cols * sizeof(int));
    int *y = (int *)malloc(rows * sizeof(int));

    printf("Enter non-zero values:\n");
    for (int i = 0; i < nnz; i++)
        scanf("%d", &data[i]);

    printf("Enter column indices:\n");
    for (int i = 0; i < nnz; i++)
        scanf("%d", &col_index[i]);

    printf("Enter row pointers:\n");
    for (int i = 0; i <= rows; i++)
        scanf("%d", &row_ptr[i]);

    printf("Enter vector:\n");
    for (int i = 0; i < cols; i++)
        scanf("%d", &x[i]);

    int *d_data, *d_col, *d_row, *d_x, *d_y;

    cudaMalloc((void **)&d_data, nnz * sizeof(int));
    cudaMalloc((void **)&d_col, nnz * sizeof(int));
    cudaMalloc((void **)&d_row, (rows + 1) * sizeof(int));
    cudaMalloc((void **)&d_x, cols * sizeof(int));
    cudaMalloc((void **)&d_y, rows * sizeof(int));

    cudaMemcpy(d_data, data, nnz * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_col, col_index, nnz * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_row, row_ptr, (rows + 1) * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, cols * sizeof(int),
               cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (rows + threads - 1) / threads;

    sparseMatVec<<<blocks, threads>>>(
        d_data, d_col, d_row, d_x, d_y, rows
    );

    cudaMemcpy(y, d_y, rows * sizeof(int),
               cudaMemcpyDeviceToHost);

    printf("Resultant Vector:\n");
    for (int i = 0; i < rows; i++)
        printf("%d\n", y[i]);

    cudaFree(d_data);
    cudaFree(d_col);
    cudaFree(d_row);
    cudaFree(d_x);
    cudaFree(d_y);

    free(data);
    free(col_index);
    free(row_ptr);
    free(x);
    free(y);

    return 0;
}
