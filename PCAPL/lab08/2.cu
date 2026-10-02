// Implement a program in CUDA to perform Odd-Even Transposition Sort in parallel.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void oddEvenSort(int *arr, int n, int phase)
{
    int i = 2 * (blockIdx.x * blockDim.x + threadIdx.x) + phase;

    if (i + 1 < n)
    {
        if (arr[i] > arr[i + 1])
        {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int *d_arr;

    cudaMalloc((void **)&d_arr, n * sizeof(int));

    cudaMemcpy(d_arr, arr, n * sizeof(int), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = ((n / 2) + threads - 1) / threads;

    for (int phase = 0; phase < n; phase++)
    {
        oddEvenSort<<<blocks, threads>>>(d_arr, n, phase % 2);
        
        cudaDeviceSynchronize();
    }

    cudaMemcpy(arr, d_arr, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    cudaFree(d_arr);
    free(arr);

    return 0;
}