/*
Implement a program in CUDA to add two matrices for the following specification:
Each column of the resultant matrix is to be computed by one thread.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void matrixAdd(int *A, int *B, int *C, int rows, int cols) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (col < cols) {
        for (int row = 0; row < rows; row++) {
            int idx = row * cols + col;
            C[idx] = A[idx] + B[idx];
        }
    }
}

int main() {
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int size = rows * cols * sizeof(int);

    int *A = (int *)malloc(size);
    int *B = (int *)malloc(size);
    int *C = (int *)malloc(size);

    printf("Enter Matrix A:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &A[i]);

    printf("Enter Matrix B:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &B[i]);

    int *d_A, *d_B, *d_C;

    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (cols + threads - 1) / threads;

    matrixAdd<<<blocks, threads>>>(d_A, d_B, d_C, rows, cols);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", C[i * cols + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}