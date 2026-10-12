// Implement a CUDA program that reads a string and replaces every vowel with '*'. Use an appropriate atomic function to replace the character with *.

#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__device__ int isVowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' ||
            c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' ||
            c == 'O' || c == 'U');
}

__device__ void atomicReplace(char *str, int index)
{
    int wordIndex = index / 4;
    int byteIndex = index % 4;

    unsigned int *address = ((unsigned int *)str) + wordIndex;
    int shift = byteIndex * 8;

    unsigned int oldValue;
    unsigned int newValue;

    do
    {
        oldValue = *address;

        newValue =
            (oldValue & ~(0xFFu << shift)) |
            ((unsigned int)'*' << shift);

    } while (atomicCAS(address,
                       oldValue,
                       newValue) != oldValue);
}

__global__ void replaceVowels(char *str, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        if (isVowel(str[i]))
            atomicReplace(str, i);
    }
}

int main()
{
    char str[500];

    printf("Enter string: ");
    fgets(str, 500, stdin);

    str[strcspn(str, "\n")] = '\0';

    int n = strlen(str);

    char *d_str;

    cudaMalloc((void **)&d_str, n + 4);

    cudaMemset(d_str, 0, n + 4);

    cudaMemcpy(d_str, str, n + 1, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    replaceVowels<<<blocks, threads>>>(d_str, n);

    cudaDeviceSynchronize();

    cudaMemcpy(str, d_str, n + 1, cudaMemcpyDeviceToHost);

    printf("Output String RS: %s\n", str);

    cudaFree(d_str);

    return 0;
}