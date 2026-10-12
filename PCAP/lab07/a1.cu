/*
Implement a program in CUDA to perform the linear algebra function of the form y = αx + y, where x and y are vectors and α is a scalar value.
*/

#include <stdio.h>
#include <cuda_runtime.h>

#define N 5

__global__ void saxpy(float alpha, float *x, float *y)
{
    int i = threadIdx.x;

    if (i < N)
        y[i] = alpha * x[i] + y[i];
}

int main()
{
    float x[N], y[N];
    float alpha;

    float *d_x, *d_y;
    int size = N * sizeof(float);

    printf("Enter %d elements (X): ", N);
    for (int i = 0; i < N; i++)
        scanf("%f", &x[i]);

    printf("Enter %d elements (Y): ", N);
    for (int i = 0; i < N; i++)
        scanf("%f", &y[i]);

    printf("Enter alpha: ");
    scanf("%f", &alpha);

    cudaMalloc((void **)&d_x, size);
    cudaMalloc((void **)&d_y, size);

    cudaMemcpy(d_x, x, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, size, cudaMemcpyHostToDevice);

    saxpy<<<1, N>>>(alpha, d_x, d_y);

    cudaMemcpy(y, d_y, size, cudaMemcpyDeviceToHost);

    printf("\ny = αx + y:\n");

    for (int i = 0; i < N; i++)
        printf("%.2f ", y[i]);

    printf("\n");

    cudaFree(d_x);
    cudaFree(d_y);

    return 0;
}