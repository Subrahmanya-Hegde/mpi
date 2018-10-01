#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int numnodes, myid, mpi_err;

#define mpi_root 0	

void init_it(int *argc, char *argv)
{
	mpi_err = MPI_Init(argc, &argv);
	mpi_err = MPI_Comm_size(MPI_COMM_WORLD, &numnodes);
	mpi_err = MPI_Comm_size(MPI_COMM_WORLD, &myid);
}

int main(int argc, char *argv[])
{

	int *myray, *sendray, *back_ray, count, size, mysize, i, k, j, total;

	init_it(&argc, &argv);

	count = 4;

	myray = (int*)malloc(count * sizeof(int));

	if(myid == mpi_root)
	{
		size = count * numnodes;

		sendray = (int*)malloc(size * sizeof(int));
		back_ray = (int*)malloc(numnodes * sizeof(int));

		for(i = 0; i < size; i++)
		{
			sendray[i] = i;
			printf("sendray = %d\n", sendray[i]);
		}
	}

	mpi_err = MPI_Scatter(sendray, count, MPI_INT, myray, count, MPI_INT, mpi_root, MPI_COMM_WORLD);
	total = 0;

	for(i = 0; i < count; i++)
	{
		total += myray[i];
		printf("myray = %d\n", myray[i]);
	}

	printf("Myid = %d Total = %d\n", myid, total);

	mpi_err = MPI_Gather(&total, 1, MPI_INT, back_ray, 1, MPI_INT, mpi_root, MPI_COMM_WORLD);
	
	if(myid == mpi_root)
	{
		total = 0;	

		for(i = 0; i < numnodes; i++)
		{
			total += back_ray[i];
		}
	}

	printf("Result : %d\n", total);

	MPI_Finalize();

	return 0;
}