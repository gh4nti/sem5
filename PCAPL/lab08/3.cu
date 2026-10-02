// Implement a program in CUDA to perform Parallel Rank Sort in parallel.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void rankSort(int *arr, int *output, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        int rank = 0;

        for (int j = 0; j < n; j++)
        {
            if (arr[j] < arr[i])
                rank++;
            
            else if (arr[j] == arr[i] && j < i)
                rank++;
        }

        output[rank] = arr[i];
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int *d_arr, *d_output;

    cudaMalloc((void **)&d_arr, n * sizeof(int));
    cudaMalloc((void **)&d_output, n * sizeof(int));

    cudaMemcpy(d_arr, arr, n * sizeof(int), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    rankSort<<<blocks, threads>>>(d_arr, d_output, n);
    
    cudaDeviceSynchronize();

    cudaMemcpy(output, d_output, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", output[i]);
    printf("\n");

    cudaFree(d_arr);
    cudaFree(d_output);

    free(arr);
    free(output);

    return 0;
}