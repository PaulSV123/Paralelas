#include <iostream>
#include <ctime>
#define MAX 400
#define r 20
#define m 20
#define n 20
using namespace std;

int main()
{
    float t0, t1, t2, t3;
    t0 = clock();
    srand(time(NULL));
    long A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    for(long i=0; i<r; ++i)
        for(long j=0; j<m; ++j)
        {
            A[i][j]= rand() % 256;
        }
    t0=clock();
    for(long i=0; i<r; ++i)
        for(long j=0; j<m; ++j)
        {
            B[i][j]= rand() % 256;
        }
    t1 = clock();
    float time1= (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time 1: "<<time1<<endl;
    t2 = clock();
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
    t3 = clock();
    float time2= (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Execution Time 2: "<<time2<<endl;
    float resultado =(time1+time2);
    cout << "\nResultado completo: "<<resultado<<endl;
    return 0;
}
