// Implement a program in CUDA to process a 1D array containing angles in radians to generate sine of the angles in the output array. Use appropriate function.

#include <stdio.h>
#include <math.h>
#include <cuda_runtime.h>

#define N 5

__global__ void findSine(float *angles, float *result)
{
    int i = threadIdx.x;

    if (i < N)
        result[i] = sinf(angles[i]);
}

int main()
{
    float angles[N];
    float result[N];

    float *d_angles, *d_result;

    int size = N * sizeof(float);

    printf("Enter %d angles in radians: ", N);

    for (int i = 0; i < N; i++)
        scanf("%f", &angles[i]);

    cudaMalloc((void **)&d_angles, size);
    cudaMalloc((void **)&d_result, size);

    cudaMemcpy(d_angles, angles, size, cudaMemcpyHostToDevice);

    findSine<<<1, N>>>(d_angles, d_result);

    cudaMemcpy(result, d_result, size, cudaMemcpyDeviceToHost);

    printf("\nSine values:\n");

    for (int i = 0; i < N; i++)
        printf("sin(%f) = %f\n", angles[i], result[i]);

    cudaFree(d_angles);
    cudaFree(d_result);

    return 0;
}