// Write a CUDA program to read a character matrix A and an integer matrix B, both of size MxN. Each character in matrix A must be repeated the number of times specified by the corresponding element in matrix B. Each element must be processed by one CUDA thread. The repeated characters should be combined into a resultant string STR in row-major order.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void repeatChars(char *A, int *B, int *offset,
                            char *STR, int total) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < total) {
        for (int j = 0; j < B[idx]; j++)
            STR[offset[idx] + j] = A[idx];
    }
}

int main() {
    int m, n;

    printf("Enter rows and columns: ");
    scanf("%d %d", &m, &n);

    int total = m * n;

    char *A = (char *)malloc(total * sizeof(char));
    int *B = (int *)malloc(total * sizeof(int));
    int *offset = (int *)malloc(total * sizeof(int));

    printf("Enter Character Matrix A:\n");
    for (int i = 0; i < total; i++)
        scanf(" %c", &A[i]);

    printf("Enter Count Matrix B:\n");
    for (int i = 0; i < total; i++)
        scanf("%d", &B[i]);

    int length = 0;

    for (int i = 0; i < total; i++) {
        if (B[i] < 0) {
            printf("Counts must be non-negative.\n");
            free(A);
            free(B);
            free(offset);
            return 1;
        }

        offset[i] = length;
        length += B[i];
    }

    char *STR = (char *)malloc((length + 1) * sizeof(char));

    char *d_A, *d_STR;
    int *d_B, *d_offset;

    cudaMalloc((void **)&d_A, total * sizeof(char));
    cudaMalloc((void **)&d_B, total * sizeof(int));
    cudaMalloc((void **)&d_offset, total * sizeof(int));
    cudaMalloc((void **)&d_STR, (length + 1) * sizeof(char));

    cudaMemcpy(d_A, A, total * sizeof(char),
               cudaMemcpyHostToDevice);

    cudaMemcpy(d_B, B, total * sizeof(int),
               cudaMemcpyHostToDevice);

    cudaMemcpy(d_offset, offset, total * sizeof(int),
               cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (total + threads - 1) / threads;

    repeatChars<<<blocks, threads>>>(
        d_A, d_B, d_offset, d_STR, total
    );

    cudaMemcpy(STR, d_STR, length * sizeof(char),
               cudaMemcpyDeviceToHost);

    STR[length] = '\0';

    printf("Resultant String: %s\n", STR);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_offset);
    cudaFree(d_STR);

    free(A);
    free(B);
    free(offset);
    free(STR);

    return 0;
}
