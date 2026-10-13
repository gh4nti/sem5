// Write a CUDA program that reads a matrix of size MxN and produces a resultant matrix such that each element of the ith row is raised to the power i, where row numbering starts from 1.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void rowPower(int *A, long long *B, int rows, int cols) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < rows * cols) {
        int row = idx / cols;
        int power = row + 1;

        long long result = 1;

        for (int i = 0; i < power; i++)
            result *= A[idx];

        B[idx] = result;
    }
}

int main() {
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int sizeA = rows * cols * sizeof(int);
    int sizeB = rows * cols * sizeof(long long);

    int *A = (int *)malloc(sizeA);
    long long *B = (long long *)malloc(sizeB);

    printf("Enter Matrix A:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &A[i]);

    int *d_A;
    long long *d_B;

    cudaMalloc((void **)&d_A, sizeA);
    cudaMalloc((void **)&d_B, sizeB);

    cudaMemcpy(d_A, A, sizeA, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (rows * cols + threads - 1) / threads;

    rowPower<<<blocks, threads>>>(d_A, d_B, rows, cols);

    cudaMemcpy(B, d_B, sizeB, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%lld ", B[i * cols + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);

    free(A);
    free(B);

    return 0;
}