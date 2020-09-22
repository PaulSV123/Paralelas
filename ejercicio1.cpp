#include <iostream>
#include <ctime>
#define MAX 500
using namespace std;
int main()
{
    srand(time(NULL));
    float t0, t1, t2, t3;
    t0 = clock();
    double A[MAX][MAX], x[MAX], y[MAX];
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            A[i][j]= rand() % 256;
            x[j]= rand() % 256;
        }
    }
    t0=clock();
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            y[i] += A[i][j]*x[j];
        }
    }
    t1 = clock();
    double time1= (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time 1: ";printf("%f",time1);cout<<endl;
    t2 = clock();

    for (int j = 0; j < MAX; j++){
        for (int i = 0; i < MAX; i++){
            y[i] += A[i][j]*x[j];
        }
    }
    t3 = clock();
    double time2= (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Execution Time 2: ";printf("%f",time2);
    return 0;
}
