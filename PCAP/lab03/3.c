/*
Implement an OpenMP program using C to determine the number of prime numbers within a given range (1 to N) using the parallel for directive. Since checking whether a number is prime requires a varying amount of computation depending on the number being tested, this problem exhibits an imbalanced workload across loop iterations.

Execute the program separately using the following OpenMP scheduling policies:
- schedule(static)
- schedule(dynamic)
- schedule(guided)

For each scheduling policy:
- Record the thread ID responsible for processing each number.
- Measure the execution time using omp_get_wtime().
- Observe how loop iterations are distributed among the threads.
- Compare the load balancing and execution time obtained with each scheduling policy.
*/

#include <stdio.h>
#include <omp.h>
#include <math.h>

int isPrime(int n);

int main()
{
	int N;
	int pc; // prime count
	double start, end;

	printf("N: ");
	scanf("%d", &N);

	// static scheduling
	pc = 0;

	printf("\n----STATIC SCHEDULING----\n");
	start = omp_get_wtime();

#pragma omp parallel for schedule(static) reduction(+ : pc)
	for (int i = 1; i <= N; i++)
	{
		int tid = omp_get_thread_num();

		if (isPrime(i))
			pc++;

		printf("%d: Thread %d\n", i, tid);
	}

	end = omp_get_wtime();

	printf("No. of primes: %d\n", pc);
	printf("Execution time: %f sec\n", end - start);

	// dynamic scheduling
	pc = 0;

	printf("\n----DYNAMIC SCHEDULING----\n");
	start = omp_get_wtime();

#pragma omp parallel for schedule(dynamic) reduction(+ : pc)
	for (int i = 1; i <= N; i++)
	{
		int tid = omp_get_thread_num();

		if (isPrime(i))
			pc++;

		printf("%d: Thread %d\n", i, tid);
	}

	end = omp_get_wtime();

	printf("No. of primes: %d\n", pc);
	printf("Execution time: %f sec\n", end - start);

	// guided scheduling
	pc = 0;

	printf("\n----GUIDED SCHEDULING----\n");
	start = omp_get_wtime();

#pragma omp parallel for schedule(guided) reduction(+ : pc)
	for (int i = 1; i <= N; i++)
	{
		int tid = omp_get_thread_num();

		if (isPrime(i))
			pc++;

		printf("%d: Thread %d\n", i, tid);
	}

	end = omp_get_wtime();

	printf("No. of primes: %d\n", pc);
	printf("Execution time: %f sec\n", end - start);

	return 0;
}

int isPrime(int n)
{
	if (n < 2)
		return 0;

	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
			return 0;
	}

	return 1;
}