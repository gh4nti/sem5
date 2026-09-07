// Implement a CUDA program to compute the Euclidean distance between two randomly initialized vectors A and B, each of length N. Keep the number of threads per block fixed at 256 and dynamically determine the number of blocks required to process all N elements.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

#define N 1000
#define THREADS 256

__global__ void euclideanKernel(float *a, float *b, float *sum)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;

	if (i < N)
	{
		float diff = a[i] - b[i];
		atomicAdd(sum, diff * diff);
	}
}

int main()
{
	float a[N], b[N];
	float sum = 0.0f;

	float *d_a, *d_b, *d_sum;
	int size = N * sizeof(float);

	for (int i = 0; i < N; i++)
    {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_sum, sizeof(float));

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_sum, &sum, sizeof(float), cudaMemcpyHostToDevice);

    int blocks = (N + THREADS - 1) / THREADS;

    euclideanKernel<<<blocks, THREADS>>>(d_a, d_b, d_sum);

    cudaMemcpy(&sum, d_sum, sizeof(float), cudaMemcpyDeviceToHost);

    float dist = sqrt(sum);

    printf("Number of elements: %d\n", N);
    printf("Threads per block: %d\n", THREADS);
    printf("Number of blocks: %d\n", blocks);
    printf("Euclidean Distance: %f\n", dist);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_sum);

    return 0;
}