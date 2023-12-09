#include <iostream>
#include "fac.hpp"
using namespace std;

int main()
{
    int n = 0;
    cout << "Please input a positive integer: ";
    cin >> n;

    
    for(int i = 1; i <= n; i++){
        printf("%d! = %d\n",i,fac(i));
    }
    cout << endl;

    return 0;
}