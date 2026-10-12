/*
Implement a program in C to reverse the digits of the following integer array of size 9. Initialize the input array to the following values.
Input array: 18, 523, 301, 1234, 2, 14, 108, 150, 1928
Output array: 81, 325, 103, 4321, 2, 41, 801, 51, 8291
*/

#include <stdio.h>
#include <omp.h>

int reverseNumber(int num)
{
	int rev = 0;

	while (num != 0)
	{
		rev = rev * 10 + (num % 10);
		num /= 10;
	}

	return rev;
}

int main()
{
	int input[9] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int output[9];

    printf("Input Array: ");
    for (int i = 0; i < 9; i++)
        printf("%d ", input[i]);
    printf("\n\n");

    #pragma omp parallel for
    for (int i = 0; i < 9; i++)
    {
    	output[i] = reverseNumber(input[i]);

    	printf("Thread %d reversed %d -> %d\n", omp_get_thread_num(), input[i], output[i]);
    }

    printf("\nInput Array: ");
    for (int i = 0; i < 9; i++)
        printf("%d ", input[i]);

    printf("\nOutput Array: ");
    for (int i = 0; i < 9; i++)
        printf("%d ", output[i]);

    printf("\n");

    return 0;
}