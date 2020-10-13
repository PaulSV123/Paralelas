#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

#define N 1000000
int *C;
int local=1;
int * merge(int *A, int list_inicio, int *B, int list_final) {
	int inicio=0, segundo=0, tercero=0;
	int tam_lista = list_inicio+list_final;
	C = (int *)malloc(tam_lista*sizeof(int));
	while ((inicio < list_inicio) && (segundo < list_final)) {
		if (A[inicio] <= B[segundo]) 
		{
			C[tercero] = A[inicio];
			tercero++; inicio++;
		} else 
		{
			C[tercero] = B[segundo];
			tercero++; segundo++;
		}
	}
	if (inicio >= list_inicio)
	{
		for (int i = tercero; i < tam_lista; i++, segundo++)
			C[i] = B[segundo];
	}
	else if (segundo >= list_final)
	{
		for (int i = tercero; i < tam_lista; i++, inicio++)
			C[i] = A[inicio];
	}
	for (int i = 0; i < list_inicio; i++)
	{
		A[i] = C[i];
	}
	for (int i = 0; i < list_final; i++)
	{
		B[i] = C[list_inicio+i];
	}
	return C;
}
void swap(int *v, int i, int j)
{
	int t;
	t = v[i];
	v[i] = v[j];
	v[j] = t;
}
void merge_sortc(int *A, int min, int max)
{
	int *C;
	int medio = (min+max)/2;
	int bajo_medio = medio - min + 1;
	int bajo_alto = max - medio;
	if (max == min) {
		return;
	} else {
		merge_sortc(A, min, medio);
		merge_sortc(A, medio+1, max);
		C = merge(A + min, bajo_medio, A + medio + 1, bajo_alto);
	}
}
int main(int argc, char **argv)
{
	int * data;
	int * inciliazador;
	int * diferencia;
	long long m,n=N;
	long long my_rank,p;
	int s = 0;
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	if(my_rank==0)
	{
		int r;
		srandom(clock());
		s = n/p;
		r = n%p;
		data = (int *)malloc((n+s-r)*sizeof(int));
		for(int i=0;i<n;i++)
			data[i] = random();
		if(r!=0)
		{
			for(int i=n;i<n+s-r;i++)
				data[i]=0;
			s=s+1;
		}
		MPI_Bcast(&s,1,MPI_INT,0,MPI_COMM_WORLD);
		inciliazador = (int *)malloc(s*sizeof(int));
		MPI_Scatter(data,s,MPI_INT,inciliazador,s,MPI_INT,0,MPI_COMM_WORLD);
		merge_sortc(inciliazador, 0, s-1);
	}
	while(local<p)
	{
		if(my_rank%(2*local)==0)
		{
			if(my_rank+local<p)
			{
				MPI_Recv(&m,1,MPI_INT,my_rank+local,0,MPI_COMM_WORLD,&status);
				diferencia = (int *)malloc(m*sizeof(int));
				MPI_Recv(diferencia,m,MPI_INT,my_rank+local,0,MPI_COMM_WORLD,&status);
				inciliazador = merge(inciliazador,s,diferencia,m);
				s = s+m;
			} 
		}
		else
		{
			int buscado = my_rank-local;
			MPI_Send(&s,1,MPI_INT,buscado,0,MPI_COMM_WORLD);
			MPI_Send(inciliazador,s,MPI_INT,buscado,0,MPI_COMM_WORLD);
			break;
		}
		local = local*2;
	}
	MPI_Finalize();
}
