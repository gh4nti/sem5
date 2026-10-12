/* Implement a CUDA program that takes a string Sin as input and one integer value N and produces an output string Sout in parallel by concatenating the input string Sin, N times.
Example:

Input:
Sin = "Hello"
N = 3

Output:
Sout = "HelloHelloHello"
*/

#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__global__ void repeatString(char *Sin, char *Sout, int len, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < len)
    {
        for (int j = 0; j < N; j++)
            Sout[j * len + i] = Sin[i];
    }
}

int main()
{
    char Sin[100];
    int N;

    printf("Enter input string: ");
    scanf("%s", Sin);

    printf("Enter N: ");
    scanf("%d", &N);

    int len = strlen(Sin);
    int outputSize = len * N;

    char Sout[1000];

    char *d_Sin, *d_Sout;

    cudaMalloc((void **)&d_Sin, len * sizeof(char));
    cudaMalloc((void **)&d_Sout, outputSize * sizeof(char));

    cudaMemcpy(d_Sin, Sin, len * sizeof(char), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (len + threads - 1) / threads;

    repeatString<<<blocks, threads>>>(
        d_Sin, d_Sout, len, N
    );

    cudaDeviceSynchronize();

    cudaMemcpy(Sout, d_Sout, outputSize * sizeof(char), cudaMemcpyDeviceToHost);

    Sout[outputSize] = '\0';

    printf("Output string Sout: %s\n", Sout);

    cudaFree(d_Sin);
    cudaFree(d_Sout);

    return 0;
}