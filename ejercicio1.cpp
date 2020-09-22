#include <iostream>
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
    float time1= (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time 1: "<<time1<<endl;
    t2 = clock();

    for (int j = 0; j < MAX; j++){
        for (int i = 0; i < MAX; i++){
            y[i] += A[i][j]*x[j];
        }
    }
    t3 = clock();
    float time2= (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Execution Time 2: "<<time2<<endl;
    return 0;
}
