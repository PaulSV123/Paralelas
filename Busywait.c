#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <stdatomic.h>
int limite=32;
pthread_t hilo_general[32];
int thread_count=32;
int flag=0;
float tiempo=0;
long long int n=pow(10,8);

void* Thread_function(void* ignore)
{
	for(int i =0;i<n;i++)
	{
		int global=0;
		sleep(0.0001);
		flag=global;
		//printf("cambio de flag %d \n",global );
	}
	return NULL;
}

void* Thread_sum(void* rank)
{
	//printf("Cantidad %d\n",cantidad);
	//printf("rankdado %p \n",rank);
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
		//printf("adsadsadsadsadsa\n",hilo_general[i]);
		//printf("asdsadsadsadasdas %ld \n",pthread_self());
		//printf("Hilo genedal %ld \n",hilo_general[flag]);
		sum += factor/(2*i+1);
	}
	while (hilo_general[flag]!=pthread_self());
	sum += my_sum;
		//flag = (flag+1) % thread_count;
		//printf("Esta corriendo tal proceso %d \n",flag);
		//if(flag+1==limite)
		//{
		//	flag=(flag+1) % thread_count;;
			//printf("asdadsadsads %lld \n",i);
		//}
		//else{
		//	flag++; //= (flag+1) % thread_count;
		//}
		//printf("valor s %lli \n",i);
		//sleep(0.000001);
		//flag++;
	//printf("Esto es una prueba de %d a la %d\n",n,thread_count);
	t_fin=clock();
	double secs=(double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	tiempo+=secs;
	flag++;
	return NULL;
}
int main(int argc, char* argv[])
{
	//clock_t t_ini,t_fin;
	//double secs;
	int error;
	//t_ini = clock();
	printf("Se crearan %d hilos\n",limite);
	//error = pthread_create(&t1, NULL, Thread_function, NULL);
	for (int i = 0; i < limite; ++i)
	{
		error = pthread_create(&hilo_general[i],NULL,&Thread_sum,NULL);
		if(error!=0)
		{
			printf("Error en la hilo\n");
		}
	}
	//pthread_join(t1, NULL);
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
	printf("Con %d hilos son %lf segundos\n",limite,tiempo/limite);
	return 0;
}
