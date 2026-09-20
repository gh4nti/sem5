/*
Implement a C program using OpenMP to process an integer array in parallel and demonstrate the use of the following synchronization constructs:
- critical
- atomic
- reduction
- master

The program should perform the following tasks:
- The master thread should initialize the array and display the total number of threads participating in the computation.
- Use the reduction clause to compute the sum of all array elements in parallel.
- Use the atomic construct to count the number of even elements in the array.
- Use the critical construct to allow each thread to safely display its thread ID and the partial sum of the array elements processed by that thread.
- After all threads complete execution, the master thread should display the final sum of the array elements and the total count of even numbers.
*/

#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
	int arr[N];
	int sum = 0;
	int ec = 0; // even count

#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		int n = omp_get_num_threads();

// master: initialization
#pragma omp master
		{
			for (int i = 0; i < N; i++)
				arr[i] = i + 1;

			printf("Total no. of threads: %d\n", n);
			printf("Array: ");
			for (int i = 0; i < N; i++)
				printf("%3d", arr[i]);
			printf("\n");
		}

#pragma omp barrier
		int ps = 0; // partial sum

#pragma omp for reduction(+ : sum)
		for (int i = 0; i < N; i++)
		{
			sum += arr[i];
			ps += arr[i];

			// atomic: count even numbers
			if (arr[i] % 2 == 0)
			{
#pragma omp atomic
				ec++;
			}
		}

// critical: safely display thread information
#pragma omp critical
		{
			printf("Thread %d: Partial sum = %d\n", tid, ps);
		}

// master: final result
#pragma omp barrier

#pragma omp master
		{
			printf("\nFinal sum = %d\n", sum);
			printf("Even numbers: %d\n", ec);
		}
	}

	return 0;
}