#include <iostream>
#include <ctime>
#define MAX 250
#define r 3
#define m 3
#define n 3
using namespace std;

int main()
{
    float t0, t1, t2, t3;
    t0 = clock();
    srand(time(NULL));
    long A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    cout<<"Inicializando la matriz A"<<endl;
    for(long i=0; i<r; ++i)
        for(long j=0; j<m; ++j)
        {
            A[i][j]= rand() % 256;
            cout<< "["<<i<<"]["<<j<<"]: "<<A[i][j]<<endl;
        }
    cout<<"Inicializando la matriz B"<<endl;
    for(long i=0; i<r; ++i)
        for(long j=0; j<m; ++j)
        {
            B[i][j]= rand() % 256;
            cout<< "["<<i<<"]["<<j<<"]: "<<B[i][j]<<endl;
        }
    long contador=1;
    for(long bi=0; bi<r; bi+=contador)
    {
        for(long bj=0; bj<r; bj+=contador)
        {
            for(long bk=0; bk<r; bk+=contador)
            {
                for(long i=0; i<n; i+=contador)
                {
                    for(long j=0; j<n; j+=contador)
                    {
                        for(long k=0; k<n; k+=contador)
                        {
                            C[i+bi][j+bj] += A[i+bi][k+bk]*B[k+bk][j+bj];
                        }
                    }
                }
            }
        }
    }
    cout<<"Matriz Resultante: "<<endl;
    for(long i=0; i<r; ++i)
    {
        for(long j=0; j<n; ++j)
        {
            cout<<"["<<C[i][j]<<""<<"]";
        }
        cout<<endl;
    }
    return 0;
}
