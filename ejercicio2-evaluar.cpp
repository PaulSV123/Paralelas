#include <iostream>
#include <ctime>
#define MAX 400
#define k 400
#define m 400
#define n 400
using namespace std;

int main()
{
    srand(time(NULL));
    float t0, t1, t2, t3;
    t0 = clock();
    long A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    for(long i=0; i<k; ++i)
        for(long j=0; j<m; ++j)
        {
            A[i][j]= rand() % 256;
        }
    t0=clock();
    for(long i=0; i<m; ++i)
        for(long j=0; j<n; ++j)
        {
            B[i][j]= rand() % 256;
        }
    t1 = clock();
    float time1= (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time 1: ";printf("%f",time1);cout<<endl;
    t2 = clock();
    for(long i=0; i<k; ++i)
        for(long j=0; j<n; ++j)
            C[i][j] = 0;

    for(long i=0; i<k; ++i)
        for(long j=0; j<n; ++j)
            for(long z=0; z<m; ++z)
                C[i][j] += A[i][z] * B[z][j];
    t3 = clock();
    float time2= (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Execution Time 2: ";printf("%f",time2);
    float resultado =(time1+time2);
    cout << "\nResultado completo: ";printf("%f",resultado);
    return 0;
}
