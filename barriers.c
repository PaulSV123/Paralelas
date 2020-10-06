#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <stdatomic.h>
#include <semaphore.h>
int sem_init(sem_t* semaphore_p,int shared, unsigned initial_val);
int sem_destroy(sem_t* semaphore_p);
int sem_post(sem_t* semaphore_p);
int sem_wait(sem_t* semaphore_p);
int pthread_mutex_init(pthread_mutex_t* mutex_p,
	const pthread_mutexattr_t* attr_p);
int pthread_mutex_destroy(pthread_mutex_t* mutex_p);
int pthread_mutex_lock(pthread_mutex_t* mutex_p);
int pthread_mutex_unlock(pthread_mutex_t* mutex_p);
pthread_t hilo_general[2];
pthread_mutex_t mutex;
int thread_count=2;
long long sum=0;
int n=pow(10,8);
float tiempo=0;
int flag=0;
int limite=2;
int counter=0;
sem_t count_sem;
sem_t barrier_sem;
sem_t semaphores[2];
int MSG_MAX=2;
char* messages[2];

void* Thread_mutex(void* rank)
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
	clock_t t_ini,t_fin;
	t_ini=clock();
	for(i=my_fisrt_i; i < my_last_i;i++, factor = -factor)
	{
		my_sum+=factor/(2*i+1);
	}
	pthread_mutex_lock(&mutex);
	sum +=my_sum;
	counter++;
	pthread_mutex_unlock(&mutex);
	while(counter < thread_count);
	//printf("Esta inicializando\n");
	t_fin=clock();
	double secs=(double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	tiempo+=secs;
	return NULL;
}


void* Thread_busywait(void* rank)
{
	long my_rank = (long) rank;
	long long factor;
	long long sum;
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
	double my_sum=0.0;
	clock_t t_ini,t_fin;
	t_ini=clock();
	for(i=my_fisrt_i; i < my_last_i;i++, factor = -factor)
	{
		sum += factor/(2*i+1);
	}
	sum += my_sum;
	counter++;
	while(counter < thread_count);
	t_fin=clock();
	double secs=(double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	tiempo+=secs;
	flag++;
	return NULL;
}

void* Send_msg_semaforo(void* rank)
{
	long my_rank = (long) rank;
	long dest = (my_rank+1) % thread_count;
	char* my_msg = malloc(MSG_MAX+sizeof(char));
	sprintf(my_msg,"Tomada de %ld a %ld", dest, my_rank);
	messages[dest] = my_msg;
	sem_init(&count_sem,1,limite);
	sem_wait(&count_sem);
	if(counter == thread_count-1)
	{
		counter = 0;
		sem_post(&count_sem);
		for(int j=0;j<thread_count-1;j++)
		{
			sem_post(&barrier_sem);
		}
	}
	else{
		counter++;
		sem_post(&count_sem);
		sem_wait(&barrier_sem);
	}
	sem_post(&semaphores[dest]);
	sem_wait(&semaphores[my_rank]);
	printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
	return NULL;
}
int main(int argc, char* argv[])
{
	int error;
	printf("Se crearan %d hilos\n",limite);
	for (int i = 0; i < limite; ++i)
	{
		error = pthread_create(&hilo_general[i],NULL,&Send_msg_semaforo,(void*)i);
		if(error!=0)
		{
			printf("Error en la hilo\n");
		}
	}
	for (int i = 0; i < limite; i++)
	{
		pthread_join(hilo_general[i],NULL);
	}
	printf("Con %d hilos son %lf milisegundos\n",limite,tiempo/limite);
	printf("La suma total %f",sum);
	return 0;
}
