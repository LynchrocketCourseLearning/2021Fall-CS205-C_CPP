#include <iostream>
using namespace std;

char* match(char*s,char ch){
    int i = 0;
    int cnt = -1;
    while(*(s+i)){
        if(*(s+i)==ch) {cnt = i;break;}
        i++;
    }
    if(cnt==-1) return NULL;
    else return (s+cnt);
}

int main(){
    char *s = new char[50];
    char ch;
    cout<<"Please input a string:"<<endl;
    cin.getline(s,50);

    cout<<"Please input a char:"<<endl;
    cin>>ch;
    char*str=match(s,ch);
    if(str){
        int i = 0;
        while(*(str+i)) {   
            cout<<*(str+i);
            i++;
        }
    }else cout<<"Not found";

    delete[] s;
}