// Implement a CUDA program to reverse a randomly initialized 1D array of size N. Assign one CUDA thread to each array element. Use 32 threads per block and calculate the number of blocks required to process all N elements.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define N 100
#define THREADS 32

__global__ void reverseArray(int *input, int *output)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
        output[N - 1 - i] = input[i];
}

int main()
{
    int a[N], result[N];
    int *d_a, *d_result;

    int size = N * sizeof(int);

    for (int i = 0; i < N; i++)
        a[i] = rand() % 100;

    printf("Array: ");
    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_result, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    int blocks = (N + THREADS - 1) / THREADS;
    reverseArray<<<blocks, THREADS>>>(d_a, d_result);

    cudaMemcpy(result, d_result, size, cudaMemcpyDeviceToHost);

    printf("\nReversed Array: ");
    for (int i = 0; i < N; i++)
        printf("%d ", result[i]);
    printf("\n");

    printf("\nThreads per block: %d\n", THREADS);
    printf("Number of blocks: %d\n", blocks);

    cudaFree(d_a);
    cudaFree(d_result);

    return 0;
}