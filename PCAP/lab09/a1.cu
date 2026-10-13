/*
Write a CUDA program that reads a matrix A of size MxN and produces a resultant matrix B such that:
- If an element of A is even, replace it with the sum of all elements in its row.
- If an element of A is odd, replace it with the sum of all elements in its column.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void matrixSum(int *A, int *B, int rows, int cols) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < rows * cols) {
        int row = idx / cols;
        int col = idx % cols;
        int sum = 0;

        if (A[idx] % 2 == 0) {
            for (int j = 0; j < cols; j++)
                sum += A[row * cols + j];
        }
        else {
            for (int i = 0; i < rows; i++)
                sum += A[i * cols + col];
        }

        B[idx] = sum;
    }
}

int main() {
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int size = rows * cols * sizeof(int);

    int *A = (int *)malloc(size);
    int *B = (int *)malloc(size);

    printf("Enter Matrix A:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &A[i]);

    int *d_A, *d_B;

    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (rows * cols + threads - 1) / threads;

    matrixSum<<<blocks, threads>>>(d_A, d_B, rows, cols);

    cudaMemcpy(B, d_B, size, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", B[i * cols + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);

    free(A);
    free(B);

    return 0;
}
