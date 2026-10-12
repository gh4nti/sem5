// Implement a program in C to simulate the all the operations of a calculator. Given inputs A and B, find the output for A+B, A-B, A*B and A/B.

#include <stdio.h>
#include <omp.h>

int main()
{
	float A, B;

	printf("Enter two numbers: ");
	scanf("%f%f", &A, &B);

	#pragma omp parallel sections shared(A, B)
	{
		#pragma omp section
		{
			printf("Thread %d: A + B = %.2f\n", omp_get_thread_num(), A + B);
		}

		#pragma omp section
		{
			printf("Thread %d: A - B = %.2f\n", omp_get_thread_num(), A - B);
		}

		#pragma omp section
        {
            printf("Thread %d: A * B = %.2f\n", omp_get_thread_num(), A * B);
        }

        #pragma omp section
        {
            if (B != 0)
                printf("Thread %d: A / B = %.2f\n", omp_get_thread_num(), A / B);
            else
                printf("Thread %d: Division by zero is not possible.\n", omp_get_thread_num());
        }
	}
}