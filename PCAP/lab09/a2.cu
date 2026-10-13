/*
Write a CUDA program that reads a square matrix of size NxN and produces a resultant matrix such that:
- Principal diagonal elements are replaced with 0.
- Elements above the principal diagonal are replaced with their factorial.
- Elements below the principal diagonal are replaced with the sum of their digits.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__device__ long long factorial(int n) {
    long long fact = 1;

    for (int i = 2; i <= n; i++)
        fact *= i;

    return fact;
}

__device__ long long digitSum(int n) {
    long long sum = 0;
    long long num = n;

    if (num < 0)
        num = -num;

    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

__global__ void matrixOperation(int *A, long long *B, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < n * n) {
        int row = idx / n;
        int col = idx % n;

        if (row == col)
            B[idx] = 0;
        else if (row < col)
            B[idx] = factorial(A[idx]);
        else
            B[idx] = digitSum(A[idx]);
    }
}

int main() {
    int n;

    printf("Enter matrix size: ");
    scanf("%d", &n);

    int sizeA = n * n * sizeof(int);
    int sizeB = n * n * sizeof(long long);

    int *A = (int *)malloc(sizeA);
    long long *B = (long long *)malloc(sizeB);

    printf("Enter Matrix A:\n");
    for (int i = 0; i < n * n; i++)
        scanf("%d", &A[i]);

    int *d_A;
    long long *d_B;

    cudaMalloc((void **)&d_A, sizeA);
    cudaMalloc((void **)&d_B, sizeB);

    cudaMemcpy(d_A, A, sizeA, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n * n + threads - 1) / threads;

    matrixOperation<<<blocks, threads>>>(d_A, d_B, n);

    cudaMemcpy(B, d_B, sizeB, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%lld ", B[i * n + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);

    free(A);
    free(B);

    return 0;
}