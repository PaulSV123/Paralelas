#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void){
	const int PING_PONG=4;
	int my_rank,comm_sz;
	int contador=0;
	int rankeado=(my_rank+1)%2;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	while(contador < PING_PONG)
	{
		if(my_rank==contador%2)
		{
			contador++;
			MPI_Send(&contador, 1,MPI_INT,rankeado,0,MPI_COMM_WORLD);
			printf("proc %d golpeo la pelota de %d van %d golpes \n",my_rank,contador,rankeado);
			//printf("van %d golpes\n",rankeado);
			//MPI_Recv(&contador, 1,MPI_INT,1,contador,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		else{
			MPI_Recv(&contador, 1,MPI_INT,rankeado,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			//MPI_Send(&contador, 1,MPI_INT,0,contador,MPI_COMM_WORLD);
			printf("proc %d golpeo la pelota de %d van %d golpes \n",my_rank,contador,rankeado);
			//printf("van %d golpes\n",rankeado);
		}
	}
	//printf("Proc %d of %d > Does anyone have a toothpick?\n",my_rank, comm_sz);
	MPI_Finalize();
	return 0;
}
