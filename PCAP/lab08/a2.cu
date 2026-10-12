// Implement a CUDA program which reads a string consisting of N words and reverses each word of it in parallel.

#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__global__ void reverseWords(char *str, int *start, int *length, int nWords)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;

    if (id < nWords)
    {
        int s = start[id];
        int len = length[id];

        for (int i = 0; i < len / 2; i++)
        {
            char temp = str[s + i];
            str[s + i] = str[s + len - 1 - i];
            str[s + len - 1 - i] = temp;
        }
    }
}

int main()
{
    char str[500];

    printf("Enter string: ");
    fgets(str, 500, stdin);

    str[strcspn(str, "\n")] = '\0';

    int n = strlen(str);

    int start[100];
    int length[100];

    int nWords = 0;

    int i = 0;

    while (i < n)
    {
        while (i < n && str[i] == ' ')
            i++;

        if (i >= n)
            break;

        start[nWords] = i;

        int len = 0;

        while (i < n && str[i] != ' ')
        {
            len++;
            i++;
        }

        length[nWords] = len;
        nWords++;
    }

    char *d_str;
    int *d_start, *d_length;

    cudaMalloc((void **)&d_str, (n + 1) * sizeof(char));
    cudaMalloc((void **)&d_start, nWords * sizeof(int));
    cudaMalloc((void **)&d_length, nWords * sizeof(int));

    cudaMemcpy(d_str, str, (n + 1) * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_start, start, nWords * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_length, length, nWords * sizeof(int), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (nWords + threads - 1) / threads;

    reverseWords<<<blocks, threads>>>(
        d_str, d_start, d_length, nWords
    );

    cudaDeviceSynchronize();

    cudaMemcpy(str, d_str, (n + 1) * sizeof(char), cudaMemcpyDeviceToHost);

    printf("Output string: %s\n", str);

    cudaFree(d_str);
    cudaFree(d_start);
    cudaFree(d_length);

    return 0;
}