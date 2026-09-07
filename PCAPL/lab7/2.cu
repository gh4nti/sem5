/*
Given two vectors of length N, implement a CUDA program that launches two kernels to perform the following tasks:

- Add two vectors
Kernel execution configuration: Block size as N

- Find the dot product of two vectors
Kernel execution configuration: N threads
*/

#include <stdio.h>
#include <cuda_runtime.h>

#define N 5

__global__ void vectorAdd(int *a, int *b, int *c)
{
	int i = threadIdx.x;

	if (i < N)
		c[i] = a[i] + b[i];
}

__global__ void vectorDot(int *a, int *b, int *dot)
{
	int i = threadIdx.x;

	if (i < N)
		atomicAdd(dot, a[i] * b[i]);
}

int main()
{
	int a[N], b[N];

	printf("Enter %d elements (A): ", N);
	for (int i = 0; i < N; i++)
		scanf("%d", &a[i]);

	printf("Enter %d elements (B): ", N);
	for (int i = 0; i < N; i++)
		scanf("%d", &b[i]);

	int c[N];
	int dot = 0;

	int *d_a, *d_b, *d_c, *d_dot;
	int size = N * sizeof(int);

	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);
	cudaMalloc((void **)&d_dot, sizeof(int));

	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

	cudaMemcpy(d_dot, &dot, sizeof(int), cudaMemcpyHostToDevice);

	vectorAdd<<<1, N>>>(d_a, d_b, d_c);
	vectorDot<<<1, N>>>(d_a, d_b, d_dot);

	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(&dot, d_dot, sizeof(int), cudaMemcpyDeviceToHost);

	printf("A + B = ");
	for (int i = 0; i < N; i++)
		printf("%d ", c[i]);

	printf("\nDot product: %d\n", dot);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	cudaFree(d_dot);

	return 0;
}