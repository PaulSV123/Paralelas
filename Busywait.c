#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <stdatomic.h>
//int limite=8;
pthread_t hilo_general[8];
int thread_count=8;
int flag=0;
int n=pow(10,8);

void* hilo(void* ignore);

void* Thread_function(void* ignore)
{
	for(int i =0;i<6;++i)
	{
		int global=0;
		sleep(1);
		flag=global;
		//printf("cambio de flag %d \n",global );
	}
	return NULL;
}

void* Thread_sum(void* rank)
{
	//printf("Cantidad %d\n",cantidad);
	printf("rankdado %p \n",rank);
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
	for(i=my_fisrt_i; i < my_last_i;i++, factor = -factor)
	{
		printf("Hilo genedal %ld \n",hilo_general[flag]);
		while (hilo_general[flag]!=my_rank);
		printf("Esta corriendo tal proceso %d \n",flag);
		sum += factor/(2*i+1);
		//flag = (flag+1) % thread_count;
		if(hilo_general[-1]==hilo_general[flag])
		{
			flag=0;
		}
		else{
			flag++;
		}
		//flag++;
	}
	//printf("Esto es una prueba de %d a la %d\n",n,thread_count);
	return NULL;
}
int main(int argc, char* argv[])
{
	int limite=8;
	int error;
	//clock_t t_ini,t_fin;
	//double secs;
	//t_ini = clock();
	printf("Se crearan %d hilos\n",limite);
	//int limite=atoi(argv[1]);
	for (int i = 0; i < limite; i++)
	{
		error = pthread_create(&hilo_general[i],NULL,&Thread_sum,NULL);
		if(error!=0)
		{
			printf("Error en la hilo\n");
		}
	}
	for (int i = 0; i < limite; i++)
	{
		pthread_join(hilo_general[i],NULL);
	}
	void* hilo(void* ignore){
		//pthread_create(&argv[1],NULL,Thread_sum,NULL0);
		printf("Hilo creado\n");
	}
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
