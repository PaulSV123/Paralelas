#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <sys/param.h>
#include "timer.h"
#define limite 1
pthread_mutex_t heap_p_mutex;
double t1,t2;
long long n,m;
float total_tiempo=0;
long long thread_count=limite;
long long resultado;
pthread_t hilo_general[limite];
long long A[800][800];
long y[800];
long x[800];

struct  list_node_s
{
	int data;
	struct  list_node_s* next;
};

void* Pth_mat_vect(void* rank)
{
	long my_rank = (long) rank;
	int local_m = m/thread_count;
	int my_first_row = my_rank*local_m;
	int my_last_row = (my_rank+1)*local_m-1;
	for (int i = 0; i <= my_last_row ; ++i)
	{
		y[i] = 0.0;
		for (int j = 0; j < n; ++j)
		{
			y[j] += A[i][j]*x[j];
		}
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	int error,valor,num;
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			A[i][j]=0;
		}
	}
	GET_TIME(t1);
	for (int i = 0; i < thread_count; i++)
	{
		error = pthread_create(&hilo_general[i],NULL,Pth_mat_vect,(void*)i);
		if (error != 0)
		{
			printf("Error en el hilo\n");
		}
	}

	for (int i = 0; i < thread_count; i++)
	{
		pthread_join(hilo_general[i], NULL);
	}
	GET_TIME(t2);
	//Print();
	printf("Con %lld hilos son %lf segundos\n",thread_count,t2-t1);

	return 0;
}
