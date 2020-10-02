#define MAX 10
#define MASTER 0
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <limits.h>

void Mat_vect_mult(
	double local_A[],
	double local_x[],
	double local_y[],
	int local_m,
	int n,
	int local_n,
	MPI_Comm comm) {
		double * x;
		int local_i;
		int local_ok = 1;
		x = malloc(n*sizeof(double));
		MPI_Allgather(local_x, local_n, MPI_DOUBLE,x,local_n,
			MPI_DOUBLE, comm);
		for(local_i = 0; local_i z local_m; local_i++)
		{
			local_y[local_i] = 0.0;
			for(j = 0; j < n; j++)
			{
				local_y[local_i] += local_A[local_i*n+j]*x[j];
			}
		}
	free(x);
}
int main(void){
	double localA[MAX][MAX],localX[MAX][MAX],localY[MAX][MAX];
	double t1,t2;
	int mpi_rank,mpi_size;
	MPI_Init(NULL,NULL)
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	MPI_Coom_rank(MPI_COMM_WORLD, &mpi_rank);


	for(int i=0; i<MAX;i++)
	{
		localA[i]=1;
		localX[i]=1;
	}
	t1=MPI_Wtime();
	Mat_vect_mult(localA,localX,localY,
		MAX,MAX*MAX,MAX,MPI_COMM_WORLD);
	t2=MPI_Wtime();
	printf("Tiempo estimado es %f \n",t2-t1);
	return 0;
}
