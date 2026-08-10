/*
Implement a multithreaded tokenizer using OpenMP. Assign the lines of a text file to threads in a round-robin fashion. Each thread should print:
- Thread ID
- Tokens extracted from its assigned lines
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_LINES 100
#define MAX_LENGTH 500
#define MAX_THREADS 16

int main()
{
    FILE *file;
    char lines[MAX_LINES][MAX_LENGTH];
    int line_count = 0;
    int num_threads;

    file = fopen("input.txt", "r");

    if (file == NULL)
    {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    while (line_count < MAX_LINES && fgets(lines[line_count], MAX_LENGTH, file) != NULL)
    {
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0';
        line_count++;
    }

    fclose(file);

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    if (num_threads > MAX_THREADS)
        num_threads = MAX_THREADS;

    omp_set_num_threads(num_threads);

    printf("\n----Multithreaded Tokenizer----\n\n");

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        for (int i = tid; i < line_count; i += total_threads)
        {
            char line[MAX_LENGTH];
            char *token;

            strcpy(line, lines[i]);

            printf("Thread %d processing line %d:\n", tid, i + 1);

            token = strtok(line, " ,.!?;:\t\n");

            while (token != NULL)
            {
                printf("  Token: %s\n", token);
                token = strtok(NULL, " ,.!?;:\t\n");
            }

            printf("\n");
        }
    }

    return 0;
}