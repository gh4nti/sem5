// Implement a program in CUDA which performs convolution operation on one-dimensional input array N of size width using a mask array M of size mask_width to produce the resultant one-dimensional array P of size width.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void convolutionKernel_1D(int *N, int *M, int *P, int width, int mask_width)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < width)
    {
        int sum = 0;
        int radius = mask_width / 2;

        for (int j = 0; j < mask_width; j++)
        {
            int idx = i - radius + j;

            if (idx >= 0 && idx < width)
                sum += N[idx] * M[j];
        }

        P[i] = sum;
    }
}

int main()
{
    int width, mask_width;

    printf("Enter input array size: ");
    scanf("%d", &width);

    printf("Enter mask size: ");
    scanf("%d", &mask_width);

    int *N = (int *)malloc(width * sizeof(int));
    int *M = (int *)malloc(mask_width * sizeof(int));
    int *P = (int *)malloc(width * sizeof(int));

    printf("Enter input array: ");
    for (int i = 0; i < width; i++)
        scanf("%d", &N[i]);
    
    printf("Enter mask array: ");
    for (int i = 0; i < mask_width; i++)
        scanf("%d", &M[i]);
    
    int *d_N, *d_M, *d_P;

    cudaMalloc((void **)&d_N, width * sizeof(int));
    cudaMalloc((void **)&d_M, mask_width * sizeof(int));
    cudaMalloc((void **)&d_P, width * sizeof(int));

    cudaMemcpy(d_N, N, width * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, mask_width * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (width + blockSize - 1) / blockSize;

    convolutionKernel_1D<<<gridSize, blockSize>>>(d_N, d_M, d_P, width, mask_width);

    cudaMemcpy(P, d_P, width * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Resultant array: ");
    for (int i = 0; i < width; i++)
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