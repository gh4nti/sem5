// Implement an OpenMP program to determine and display the total number of threads participating in a parallel region using the omp_get_num_threads() runtime function.

#include <stdio.h>
#include <omp.h>

int main()
{

#pragma omp parallel
	{
#pragma omp single
		{
			int total_threads = omp_get_num_threads();
			printf("Total number of threads: %d\n", total_threads);
		}
	}

	return 0;
}