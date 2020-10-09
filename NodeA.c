#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <sys/param.h>
#include "timer.h"
#define limite 8
const int MAX = 100000;
pthread_mutex_t heap_p_mutex;
double t1,t2;
float total_tiempo=0;
long long thread_count=limite;
long long resultado;
pthread_t hilo_general[limite];
struct  list_node_s
{
	int data;
	struct  list_node_s* next;
	pthread_mutex_t mutex;
};

struct list_node_s* heap_p;

int Member(int value, struct list_node_s* heap_p)
{
	struct list_node_s* temp_p;
	pthread_mutex_lock(&heap_p_mutex);
	temp_p=heap_p;
	while(temp_p != NULL && temp_p->data < value)
	{
		if(temp_p->next !=NULL)
			pthread_mutex_lock(&heap_p_mutex);
		if(temp_p == heap_p)
			pthread_mutex_unlock(&heap_p_mutex);
		pthread_mutex_unlock(&(temp_p->mutex));
		temp_p = temp_p->next;
	}
	if(temp_p == NULL || temp_p->data > value)
	{
		if(temp_p == heap_p)
		{
			pthread_mutex_unlock(&heap_p_mutex);
		}
		if(temp_p != NULL)
		{
			pthread_mutex_unlock(&(temp_p->mutex));
		}
		return 0;
	}
	else
	{
		if(temp_p == heap_p)
		{
			pthread_mutex_unlock(&heap_p_mutex);
		}
		pthread_mutex_unlock(&(temp_p->mutex));
		return 1;
	}
}

int Insert(int value, struct list_node_s** heap_p)
{
	struct list_node_s* curr_p = *heap_p;
	struct list_node_s* pred_p = NULL;
	struct list_node_s* temp_p;

	while(curr_p != NULL && curr_p->data < value)
	{
		pred_p = curr_p;
		curr_p = curr_p->next;
	}

	if(curr_p == NULL || curr_p->data > value)
	{
		temp_p = malloc(sizeof(struct list_node_s));
		temp_p->data = value;
		temp_p->next = curr_p;
		//rintf("Ingresado\n");
		if (pred_p == NULL)
		{
			*heap_p = temp_p;
			//printf("Ingresado\n");
		}
		else
		{
			pred_p->next = temp_p;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int Delete(int value, struct list_node_s** heap_p)
{
	struct list_node_s* curr_p = *heap_p;
	struct list_node_s* pred_p = NULL;
	while(curr_p != NULL && curr_p->data < value)
	{
		pred_p = curr_p;
		curr_p = curr_p->next;
	}

	if(curr_p == NULL || curr_p->data > value)
	{
		if (pred_p == NULL)
		{
			*heap_p = curr_p->next;
			free(curr_p);
		}
		else
		{
			pred_p->next = curr_p->next;
			free(curr_p);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

void Print(void)
{
	struct list_node_s* temp;
	printf("lista = \n");
	temp=heap_p;
	while(temp != (struct list_node_s*) NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next; 
	}
	printf("\n");
}

int Random(void* rank)
{
	long my_rank = (long) rank;
	int limitador=1000;
	int Total = MAX/limite;
	int M = 80*Total/100;
	int I = 10*Total/100;
	int D = 10*Total/100;
	for (int i = 0; i < M; i++)
	{
		resultado=rand() % limitador;
		Member(resultado,&heap_p);
	}
	for (int j = 0; j < I; j++)
	{
		Insert(j,&heap_p);
	}
	for (int k = 0; k < D; k++)
	{
		Delete(k,&heap_p);
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	heap_p = (struct list_node_s *) malloc(sizeof(struct list_node_s));
	int error,valor,num;
	for (int i = 0; i < 1000; i++)
	{
		Insert(i,&heap_p);
	}
	pthread_mutex_init(&heap_p_mutex, NULL);
	GET_TIME(t1);
	for (int i = 0; i < limite; i++)
	{
		error = pthread_create(&hilo_general[i],NULL,&Random,NULL);
		if (error != 0)
		{
			printf("Error en el hilo\n");
		}
	}

	for (int i = 0; i < limite; i++)
	{
		pthread_join(hilo_general[i], NULL);
	}
	GET_TIME(t2);
	//Print();
	printf("Con %lld hilos son %lf segundos\n",thread_count,t2-t1);

	return 0;
}
