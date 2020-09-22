#include <iostream>
#include <ctime>
#define MAX 400
#define k 1000
#define m 1000
#define n 1000
using namespace std;

int main()
{
    srand(time(NULL));
    long A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    cout<<"Inicializando la matriz A"<<endl;
    for(long i=0; i<k; ++i)
        for(long j=0; j<m; ++j)
        {
            A[i][j]= rand() % 256;
            cout<< "["<<i<<"]["<<j<<"]: "<<A[i][j]<<endl;
        }
    cout<<"Inicializando la matriz B"<<endl;
    for(long i=0; i<m; ++i)
        for(long j=0; j<n; ++j)
        {
            B[i][j]= rand() % 256;
            cout<< "["<<i<<"]["<<j<<"]: "<<B[i][j]<<endl;
        }
    for(long i=0; i<k; ++i)
        for(long j=0; j<n; ++j)
            C[i][j] = 0;

    for(long i=0; i<k; ++i)
        for(long j=0; j<n; ++j)
            for(long z=0; z<m; ++z)
                C[i][j] += A[i][z] * B[z][j];

    cout<<"Matriz A: "<<endl;
    for(long i=0; i<k; ++i)
    {
        for(long j=0; j<m; ++j)
        {
            cout<<"["<<A[i][j]<<""<<"]";
        }
        cout<<endl;
    }

    cout<<"Matriz B: "<<endl;
    for(long i=0; i<m; ++i)
    {
        for(long j=0; j<n; ++j)
        {
            cout<<"["<<B[i][j]<<""<<"]";
        }
        cout<<endl;
    }

    cout<<"Matriz Resultante: "<<endl;
    for(long i=0; i<k; ++i)
    {
        for(long j=0; j<n; ++j)
        {
            cout<<"["<<C[i][j]<<""<<"]";
        }
        cout<<endl;
    }

    return 0;
}
