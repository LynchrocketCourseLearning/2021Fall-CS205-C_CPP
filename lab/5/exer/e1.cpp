#include<iostream>
using namespace std;

int main(){
    int * arr = new int[5]{1,2,3,4,5};
    for (int i = 4; i >= 0; i--)
    {
        cout<< *(arr+i) << " ";
    }
    cout<<endl;
    delete[] arr;
    return 0;
}
