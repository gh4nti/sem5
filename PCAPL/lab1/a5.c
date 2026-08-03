/*
Implement a C program to read two strings S1 and S2 of same length and produce the resultant string as shown below.
S1: string
S2: length
Resultant String: slternigntgh
*/

#include <stdio.h>
#include <string.h>
#include <omp.h>

int main()
{
    char s1[100], s2[100], result[200];
    int n;

    printf("Enter first string: ");
    scanf("%s", s1);

    printf("Enter second string: ");
    scanf("%s", s2);

    if (strlen(s1) != strlen(s2))
    {
        printf("Error: Strings must be of the same length.\n");
        return 1;
    }

    n = strlen(s1);

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        result[2 * i] = s1[i];
        result[2 * i + 1] = s2[i];

        printf("Thread %d processed index %d\n",
               omp_get_thread_num(), i);
    }

    result[2 * n] = '\0';

    printf("\nResultant String: %s\n", result);
    return 0;
}