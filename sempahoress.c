#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <semaphore.h>
sem_t count_sem;
sem_t barrier_sem;
sem_t semaphores[2];
int MSG_MAX=2;
char* messages[2];
double f(double x)
{
	return x*x;
}

double Trap(){
	double left_endpt;
	double right_endpt;
	int trap_count;
	double base_len;
	double estimate;
	double x;
	int i;
	messages[dest] = my_msg;
	sem_init(&count_sem,1,limite);
	sem_wait(&count_sem);
	estimate = (f(left_endpt)+f(right_endpt))/2.0;
	for(i = 1; i<= trap_count-1;i++)
	{
		x=left_endpt + i*base_len;
		estimate += f(x);
	}
	estimate = estimate*base_len;
	printf("Paso el hilo\n");
	sem_post(&semaphores[dest]);
	sem_wait(&semaphores[my_rank]);
	printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
	return estimate;
}

int main(void){
	int my_rank, comm_sz, n=16384, local_n;
	double a = 0.0, b=3.0, h, local_a, local_b;
	double local_int, total_int;
	double t1,t2;
	int source;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	h=(b-a)/n;
	local_n = n/comm_sz;

	local_a = a+ my_rank*local_n*h;
	local_b = local_a + local_n*h;
	local_int = Trap(local_a, local_b, local_n, h);

	t1=MPI_Wtime();
	MPI_Reduce(&local_int,&total_int,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(my_rank == 0)
	{
		printf("With n = %d trapesoides, our estimate\n",n);
		printf("of the integral from %f to %f = %.15e\n",
			a,b,total_int);
	}
	t2=MPI_Wtime();
	printf("Tiempo estimado es %f \n",t2-t1);
	MPI_Finalize();
	return 0;
}
