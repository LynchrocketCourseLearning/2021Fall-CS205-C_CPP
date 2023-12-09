#include<cstring>
#include<iostream>
#include "BigInt.h"

using std::cout;
using std::endl;

int add( int* arr1, int len1, int* arr2, int len2, int* arr3, int len3 ) {
    int len = (len1 > len2) ? len1 : len2;
    if( len3 < len ) {
        return -1;
    }
    memset( arr3, 0, sizeof(int)*len3 );
    int up = 0;
    for( int i = 0; i < len; ++ i ) {
        int n1 = (i<len1) ? arr1[i] : 0;
        int n2 = (i<len2) ? arr2[i] : 0;
        int n = n1+n2+up;
        arr3[i] = n%10;
        up = n/10;
    }
    if( !up )
        return len;
    if( len3 == len )
        return -1;
    arr3[len] = up;
    return len+1;
}

int readInt( char* number, int* arr, int len ) {
    int slen = strlen(number);
    if( len < slen )
        return -1;
    for( int i = 0; i < slen; ++ i )
        arr[i] = number[slen-1-i]-'0';
    return slen;
}

void printInt( int* arr, int len ) {
    for( int i = len-1; i >= 0; -- i )
        cout<<arr[i];
    cout<<endl;
}