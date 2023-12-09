#include<iostream>
#include "DayInfo.cpp"
using namespace std;

int main(){
    cout<<"Please input the number of dayinfo and weather"<<endl;
    int n = 0;
    int m = 0;
    cin>>n;
    cin>>m;
    struct DayInfo d;
    d.day =(Day) n;
    d.wea =(Weather) m;
    if(canTravel(d))cout<<"ok"<<endl;
    else cout<<"not OK"<<endl;
    
    return 0;
}
