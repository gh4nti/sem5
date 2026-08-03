/*
Implement an OpenMP program to reverse the digits of every element in the following array:
18, 523, 301, 1234, 2, 14, 108, 150, 1928
Output:
81, 325, 103, 4321, 2, 41, 801, 51, 8291
*/

#include <stdio.h>
#include <omp.h>

int reverse(int n);

int main()
{
    int A[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Original Array:\n");
    for(int i = 0; i < n; i++)
        printf("%6d", A[i]);

    printf("\n");

    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        A[i] = reverse(A[i]);
        printf("Element %d processed by Thread %d\n",
               i, omp_get_thread_num());
    }

    printf("\nReversed Array:\n");
    for(int i = 0; i < n; i++)
        printf("%6d", A[i]);

    printf("\n");

    return 0;
}

int reverse(int n)
{
    int rev = 0;

    while(n > 0)
    {
        rev = rev * 10 + n % 10;
        n /= 10;
    }

    return rev;
}