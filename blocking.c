#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
	int nt, rank, dest, src, rc, count, tag = 1;
	char outmsg = 'x', inmsg;

	MPI_Status stat;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nt);

	if(rank == 0)
	{
		if(nt > 2)
		{
			printf("Only 2 are needed\n");
		}
		dest = src = 1;

		rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
		rc = MPI_Recv(&inmsg, 1, MPI_CHAR, src, tag, MPI_COMM_WORLD, &stat);
	}


	else if(rank == 1)
	{
		src = dest = 0;
		rc = MPI_Recv(&inmsg, 1, MPI_CHAR, src, tag, MPI_COMM_WORLD, &stat);
		rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}

	else
	{
		rc = MPI_Get_count(&stat, MPI_CHAR, &count);

		printf("Task %d recvd %d chars from %d with %d status\n", rank, count, stat, stat.MPI_TAG);
	}

	MPI_Finalize();

	return 0;
}