#include <iostream>
using namespace std;

template<typename T> T minimum(T &a, T&b){
    return (a < b) ?  a : b;
}
// template int minimum<int>(int, int);

int main(){
    int ina = 10, inb = 5;
    char cha = 'a', chb = 's';
    float fla = 10.93f, flb = 20.32f;

    
    
    cout<< "(int) " << minimum<int>(ina, inb) <<endl;
    cout<< "(char) " << minimum<char>(cha, chb) <<endl;
    cout<< "(float) " << minimum<float>(fla, flb) <<endl;
}