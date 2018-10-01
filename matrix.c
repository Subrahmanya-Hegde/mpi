#include <stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int mat[4][4], b[4], recbuf[4], gathered_arr[4], sum = 0;

	if(rank == 0)
	{
		printf("Enter matrix : \n");
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				scanf("%d", &mat[i][j]);
			}
		}
		printf("Enter 2nd matrix : \n");
		for(int i = 0; i < 4; i++)
			scanf("%d", &b[i]);
	}

	MPI_Scatter(&mat, 4, MPI_INT, recbuf, 4, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&b, 4, MPI_INT, 0, MPI_COMM_WORLD);

	for(int i = 0; i < 4; i++)
	{
		printf("Rank : %d\tRec_Buf : %d\n", rank, recbuf[i]);
	}

	for(int j = 0; j < 4; j++)
	{
		sum = sum + recbuf[j] * b[j];
	}

	printf("Rank : %d\t Result : %d\n", rank, sum);

	MPI_Gather(&sum, 1, MPI_INT, &gathered_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0)
	{
		for(int i = 0; i < 4; i++)
		{
			printf("Gathered array : %d\t", gathered_arr[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
	return 0;
}