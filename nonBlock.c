#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
	int rank, size, next, prev, buf[2], tag1 = 1, tag2 = 2;

	MPI_Request reqs[4];
	MPI_Status stat[2];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	prev = rank - 1;
	next = rank + 1;

	if(rank == 0)
	{
		prev = size - 1;
	}

	if(rank == (size-1))
	{
		next = 0;
	}

	MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);

	MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[3]);

	MPI_Waitall(4, reqs, stat);

	printf("Task %d communicated with task %d and %d\n", rank, prev, next);

	return 0;
}