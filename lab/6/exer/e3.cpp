#include <iostream>
using namespace std;
struct point
{
    float x;
    float y;
};

void init(point init, point &target){
    target.x = init.x;
    target.y = init.y;
}

void mid(point *tar1, point *tar2){
    cout<<"("<<(tar1->x+tar2->x)/2 <<","<<(tar1->y+tar2->y)/2<<")"<<endl;
}

int main(){
    point a = {1.0f,2.0f};
    point b;
    init(a,b);
    cout<<b.x<<" "<<b.y<<endl;
    point c = {2.0f,5.0f};
    mid(&a, &c);
}