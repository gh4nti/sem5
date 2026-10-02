/*
Implement a CUDA program that reads a string S and produces the string RS as follows:
Input string S:  PCAP
Output string RS: PCAPPCAPCP
*/

#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__global__ void generateString(char *S, char *RS, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        int charsToCopy = n - i;

        int start = i * n - (i * (i - 1)) / 2;

        for (int j = 0; j < charsToCopy; j++)
            RS[start + j] = S[j];
    }
}

int main()
{
    char S[100];

    printf("Enter string S: ");
    scanf("%s", S);

    int n = strlen(S);
    int outputSize = n * (n + 1) / 2;
    char RS[1000];

    char *d_S, *d_RS;

    cudaMalloc((void **)&d_S, n * sizeof(char));
    cudaMalloc((void **)&d_RS, outputSize * sizeof(char));

    cudaMemcpy(d_S, S, n * sizeof(char), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    generateString<<<blocks, threads>>>(d_S, d_RS, n);

    cudaDeviceSynchronize();

    cudaMemcpy(RS, d_RS, outputSize * sizeof(char), cudaMemcpyDeviceToHost);

    RS[outputSize] = '\0';

    printf("Output string RS: %s\n", RS);

    cudaFree(d_S);
    cudaFree(d_RS);

    return 0;
}