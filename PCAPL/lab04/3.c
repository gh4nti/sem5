// Implement a program in MPI where even ranked process prints factorial of the rank and odd ranked process prints rank's Fibonacci number.

#include <stdio.h>
#include <mpi.h>

int fact(int n);
int fib(int n);

int main(int argc, char *argv[])
{
	int rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank % 2 == 0)
		printf("Process %d: %d! = %d\n", rank, rank, fact(rank));
	
	else
		printf("Process %d: Fibonacci number at %d = %d\n", rank, rank, fib(rank));

	MPI_Finalize();
	return 0;
}

int fact(int n)
{
	int f = 1;

	for (int i = 1; i <= n; i++)
		f *= i;

	return f;
}

int fib(int n)
{
	if (n == 0)
		return 0;

	if (n == 1)
		return 1;

	return fib(n - 1) + fib(n - 2);
}