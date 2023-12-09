#include "BigInt.h"

#include<iostream>
using std::endl;
using std::cout;
using std::cin;

#define NUM 1000

int main() {

    char ch1[NUM];
    char ch2[NUM];

    int arr1[NUM];
    int arr2[NUM];
    int arr3[NUM];

    cout<<"Input first number:"<<endl;
    cin>>ch1;
    cout<<"Input second number:"<<endl;
    cin>>ch2;
    int len1 = readInt( ch1, arr1, NUM );
    int len2 = readInt( ch2, arr2, NUM );
    int len3 = add( arr1, len1, arr2, len2, arr3, NUM );

    printInt(arr1, len1);
    printInt(arr2, len2);
    printInt(arr3, len3);

return 0;
}