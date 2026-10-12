// Implement a program in CUDA which performs convolution operation on one-dimensional input array N of size width using a mask array M of size mask_width to produce the resultant one-dimensional array P of size width.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void convolution1D(int *N, int *M, int *P, int n, int k)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        int sum = 0;
        int radius = k / 2;

        for (int j = 0; j < k; j++)
        {
            int idx = i - radius + j;

            if (idx >= 0 && idx < n)
                sum += N[idx] * M[j];
        }

        P[i] = sum;
    }
}

int main()
{
    int n, k;

    printf("Enter input array size: ");
    scanf("%d", &n);

    printf("Enter mask size: ");
    scanf("%d", &k);

    int *N = (int *)malloc(n * sizeof(int));
    int *M = (int *)malloc(k * sizeof(int));
    int *P = (int *)malloc(n * sizeof(int));

    printf("Enter input array: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &N[i]);
    
    printf("Enter mask array: ");
    for (int i = 0; i < k; i++)
        scanf("%d", &M[i]);
    
    int *d_N, *d_M, *d_P;

    cudaMalloc((void **)&d_N, n * sizeof(int));
    cudaMalloc((void **)&d_M, k * sizeof(int));
    cudaMalloc((void **)&d_P, n * sizeof(int));

    cudaMemcpy(d_N, N, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, k * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;

    convolution1D<<<gridSize, blockSize>>>(d_N, d_M, d_P, n, k);

    cudaMemcpy(P, d_P, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Resultant array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", P[i]);
    printf("\n");

    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    free(N);
    free(M);
    free(P);

    return 0;
}