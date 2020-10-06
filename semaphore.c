#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <stdatomic.h>
#include <sys/types.h>
#include <semaphore.h>

int sem_init(sem_t* semaphore_p,int shared, unsigned initial_val);
int sem_destroy(sem_t* semaphore_p);
int sem_post(sem_t* semaphore_p);
int sem_wait(sem_t* semaphore_p);
int thread_count=64;
int limite=64;
pthread_t hilo_general[64];
int MSG_MAX=64;
char* messages[64];
sem_t semaphores[64];

void* Send_msg_semaforo(void* rank)
{
	long my_rank = (long) rank;
	long dest = (my_rank+1) % thread_count;
	char* my_msg = malloc(MSG_MAX+sizeof(char));
	sprintf(my_msg,"Tomada de %ld a %ld", dest, my_rank);
	messages[dest] = my_msg;
	sem_post(&semaphores[dest]);
	sem_wait(&semaphores[my_rank]);
	printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
	return NULL;
}
int main(int argc, char const *argv[])
{
	int error;
	//t_ini = clock();
	printf("Se crearan %d hilos\n",limite);
	//error = pthread_create(&cambio, NULL,&Send_msg_semaforo, NULL);
	for (int i = 0; i < limite; ++i)
	{
		error = pthread_create(&hilo_general[i],NULL,&Send_msg_semaforo,(void*)i);
		if(error!=0)
		{
			printf("Error en la hilo\n");
		}
	}
	//pthread_join(cambio, NULL);
	for (int i = 0; i < limite; i++)
	{
		pthread_join(hilo_general[i],NULL);
	}
	return 0;
}
