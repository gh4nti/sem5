/*
Implement a C program to read a word of length N and produce the pattern as shown in the example.
Example: Input: PCBD Output: PCCBBBDDDD
*/

#include <stdio.h>
#include <string.h>
#include <omp.h>

int main()
{
    char str[100];
    int n;

    printf("Enter a word: ");
    scanf("%s", str);

    n = strlen(str);

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
#pragma omp critical
        {
            printf("Thread %d: ", omp_get_thread_num());

            for (int j = 0; j <= i; j++)
                printf("%c", str[i]);

            printf("\n");
        }
    }

    printf("\nPattern: ");
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            printf("%c", str[i]);

    printf("\n");

    return 0;
}