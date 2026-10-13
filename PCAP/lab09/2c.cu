/*
Implement a program in CUDA to multiply two matrices for the following specification:
Each element of the resultant matrix is to be computed by one thread.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void matrixMul(int *A, int *B, int *C,
                          int m, int n, int p) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < m * p) {
        int row = idx / p;
        int col = idx % p;

        int sum = 0;

        for (int k = 0; k < n; k++)
            sum += A[row * n + k] * B[k * p + col];

        C[idx] = sum;
    }
}

int main() {
    int m, n, p;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &m, &n);

    printf("Enter columns of Matrix B: ");
    scanf("%d", &p);

    int sizeA = m * n * sizeof(int);
    int sizeB = n * p * sizeof(int);
    int sizeC = m * p * sizeof(int);

    int *A = (int *)malloc(sizeA);
    int *B = (int *)malloc(sizeB);
    int *C = (int *)malloc(sizeC);

    printf("Enter Matrix A:\n");
    for (int i = 0; i < m * n; i++)
        scanf("%d", &A[i]);

    printf("Enter Matrix B:\n");
    for (int i = 0; i < n * p; i++)
        scanf("%d", &B[i]);

    int *d_A, *d_B, *d_C;

    cudaMalloc((void **)&d_A, sizeA);
    cudaMalloc((void **)&d_B, sizeB);
    cudaMalloc((void **)&d_C, sizeC);

    cudaMemcpy(d_A, A, sizeA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeB, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (m * p + threads - 1) / threads;

    matrixMul<<<blocks, threads>>>(d_A, d_B, d_C, m, n, p);

    cudaMemcpy(C, d_C, sizeC, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++)
            printf("%d ", C[i * p + j]);
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
