// Implement a program in CUDA to count the number of times a given word is repeated in a sentence using an atomic function.

#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__device__ int isMatch(char *sentence, char *word, int start, int wordLength, int sentenceLength)
{
    if (start + wordLength > sentenceLength)
        return 0;

    for (int i = 0; i < wordLength; i++)
    {
        if (sentence[start + i] != word[i])
            return 0;
    }

    if (start > 0 && sentence[start - 1] != ' ')
        return 0;

    if (start + wordLength < sentenceLength &&
        sentence[start + wordLength] != ' ')
        return 0;

    return 1;
}

__global__ void countWord(char *sentence, char *word, int sentenceLength, int wordLength, int *count)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < sentenceLength)
    {
        if (isMatch(sentence, word, i, wordLength, sentenceLength))
            atomicAdd(count, 1);
    }
}

int main()
{
    char sentence[500];
    char word[100];

    printf("Enter sentence: ");
    fgets(sentence, 500, stdin);

    printf("Enter word to search: ");
    scanf("%s", word);

    sentence[strcspn(sentence, "\n")] = '\0';

    int sentenceLength = strlen(sentence);
    int wordLength = strlen(word);

    char *d_sentence, *d_word;
    int *d_count;

    int count = 0;

    cudaMalloc((void **)&d_sentence, (sentenceLength + 1) * sizeof(char));
    cudaMalloc((void **)&d_word, (wordLength + 1) * sizeof(char));
    cudaMalloc((void **)&d_count, sizeof(int));

    cudaMemcpy(d_sentence, sentence, (sentenceLength + 1) * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, (wordLength + 1) * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (sentenceLength + threads - 1) / threads;

    countWord<<<blocks, threads>>>(
        d_sentence,
        d_word,
        sentenceLength,
        wordLength,
        d_count
    );

    cudaDeviceSynchronize();

    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Number of occurrences of \"%s\" = %d\n", word, count);

    cudaFree(d_sentence);
    cudaFree(d_word);
    cudaFree(d_count);

    return 0;
}