#include<stdio.h>
#include<mpi.h>

typedef long long ABC;

int main(int argc, char *argv[])
{
	int n = 0, rank, size, first, last, i;

	ABC prod  = 1, result, root = 0;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank == root	)
	{
		printf("Enter the number ");
		scanf("%d", &n);
	}

	MPI_Bcast(&n, 1, MPI_LONG_LONG, root, MPI_COMM_WORLD);

	first = (rank * n) / size;
	last = ((rank + 1) * n/ size);

	for(i = first + 1; i <= last; i++)
	{
		prod *= i;
	}

	MPI_Reduce(&prod, &result, 1, MPI_LONG_LONG, MPI_PROD, root, MPI_COMM_WORLD);

	if(rank == root)
	{
		printf("Result : ", result);
	}

	MPI_Finalize();
	
	return 0;
}