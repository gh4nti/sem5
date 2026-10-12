/*
Implement an OpenMP program to compute the sum of the first N natural numbers in parallel. Using the same program, demonstrate the effect of the following OpenMP data-sharing clauses:
- shared
- private
- firstprivate
- lastprivate

For each case:
- Execute the program.
- Observe the output produced.
- Explain the effect of the data-sharing clause on:
- Variable values
- Data accessibility among threads
- Correctness of the final result

Finally, compare the outputs obtained for each data-sharing clause and explain why they differ.
*/

#include <stdio.h>
#include <omp.h>

int main()
{
	int N;
	long long sum;

	printf("N: ");
	scanf("%d", &N);

	// shared
	sum = 0;

#pragma omp parallel for shared(sum)
	for (int i = 1; i <= N; i++)
		sum += i;

	printf("\nshared: sum = %lld\n", sum);

	// private
	sum = 0;

#pragma omp parallel for private(sum)
	for (int i = 1; i <= N; i++)
		sum += i;

	printf("private: sum = %lld\n", sum);

	// firstprivate
	sum = 0;

#pragma omp parallel for firstprivate(sum)
	for (int i = 1; i <= N; i++)
		sum += i;

	printf("firstprivate: sum = %lld\n", sum);

	// lastprivate
	sum = 0;

#pragma omp parallel for lastprivate(sum)
	for (int i = 1; i <= N; i++)
		sum += i;

	printf("lastprivate: sum = %lld\n", sum);

	return 0;
}