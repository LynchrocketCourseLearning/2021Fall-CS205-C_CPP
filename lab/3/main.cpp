#include <iostream>
#include "fib.hpp"
using namespace std;

int main()
{
    int n = 0;
    cout << "Please input a positive integer: ";
    cin >> n;

    
    do{
        cout << fib(n) << "   ";
        n--;
        if(n%10==0)printf("\n");
    }while(n);
    cout << endl;

    return 0;
}