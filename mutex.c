#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

int pthread_mutex_init(pthread_mutex_t* mutex_p,
	const pthread_mutexattr_t* attr_p);

int pthread_mutex_destroy(pthread_mutex_t* mutex_p);

int pthread_mutex_lock(pthread_mutex_t* mutex_p);

int pthread_mutex_unlock(pthread_mutex_t* mutex_p);

pthread_t hilo_general[8];
pthread_mutex_t mutex;
int thread_count=8;
long long sum=0;
int n=pow(10,8);

void* Thread_sum(void* rank)
{
	long my_rank = (long) rank;
	double factor;
	double my_sum=0.0;
	long long i;
	long long my_n = n/thread_count;
	long long my_fisrt_i = my_n+my_rank;
	long long my_last_i = my_fisrt_i + my_n;

	if (my_fisrt_i % 2 == 0)
	{
		factor = 1.0;
	}
	else
		factor = -1.0;
	for(i=my_fisrt_i; i < my_last_i;i++, factor = -factor)
	{
		my_sum+=factor/(2*i+1);
	}
	pthread_mutex_lock(&mutex);
	sum +=my_sum;
	pthread_mutex_unlock(&mutex);
	printf("Esto es una prueba de %ld a %d\n",my_rank,thread_count);
	return NULL;
}
int main(int argc, char* argv[])
{
	int limite=8;
	int error;
	printf("Se crearan %d hilos\n",limite);
	for (int i = 0; i < limite; ++i)
	{
		error = pthread_create(&hilo_general[i],NULL,Thread_sum,NULL);
		if(error!=0)
		{
			printf("Error en la hilo\n");
		}
	}
	for (int i = 0; i < limite; i++)
	{
		pthread_join(hilo_general[i],NULL);
	}
	//pthread_t hilo1,hilo2;
	//clock_t t_ini,t_fin;
	//double secs;
	//t_ini = clock();
	//pthread_create(&hilo1,NULL,Thread_sum,NULL);
	//printf("Inicio del primer hilo\n");
	//pthread_create(&hilo2,NULL,Thread_function,NULL);
	//pthread_join(hilo1,NULL);
	//pthread_join(hilo2,NULL);
	//t_fin = clock();
	//secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	//printf("%lf milisegundos\n",secs*1000.0);
	return 0;
}
