#include <iostream>
#include <cmath>
using namespace std;

int vabs(int* p , int n){
    int res = abs(*p);
    for (size_t i = 1; i < n; i++)
    {
        res += abs(*(p+i));
    }
    return res;
}

float vabs(float* p , int n){
    float res = abs(*p);
    for (size_t i = 1; i < n; i++)
    {
         res += abs(*(p+i));
    }
    return res;
}

double vabs(double* p , int n){
    double res = abs(*p);
    for (size_t i = 1; i < n; i++)
    {
         res += abs(*(p+i));
    }
    return res;
}

int main(){
    int arr_int[] = {5,-2,3,-4,-5};
    float arr_float[] = {1.2f, 43.5f, 39248.03f, 219.3f, 942.23f};
    double arr_double[] = {1.2, 4322.43, 543.54, 3298, 34.3};

    cout<<vabs(arr_int,5)<<endl;
    cout<<vabs(arr_float,5)<<endl;
    cout<<vabs(arr_double,5)<<endl;
}