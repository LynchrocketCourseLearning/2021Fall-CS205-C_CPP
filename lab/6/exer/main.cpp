#include "e1.cpp"
int main(){
    int a = 100, b = 50;
    swap1(a,b);
    cout<<a<<" "<<b<<endl;

    a = 100, b = 50;
    swap2(&a,&b);
    cout<<a<<" "<<b<<endl;

    a = 100, b = 50;
    swap3(a,b);
    cout<<a<<" "<<b<<endl;
}