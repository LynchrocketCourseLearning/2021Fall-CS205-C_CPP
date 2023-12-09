#include <iostream>
using namespace std;

void swap1(int a, int b){
    int tmp = a;
    a = b;
    b = tmp;
}
void swap2(int*a, int*b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void swap3(int&a, int&b){
    int tmp = a;
    a = b;
    b = tmp;
}
