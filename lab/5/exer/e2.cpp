#include<iostream>
using namespace std;

int main(){
    int n;
    cout<<"Please input the length of string."<<endl;
    cin>>n;
    char*p = (char*)malloc(n*sizeof(char));

    cout<<"Please input the string."<<endl;
    for (int i = 0; i < n; i++)
    {
        cin >> *(p+i);
        *(p+i) = *(p+i) + 1;
    }
    
    for (int i = 0; i < n; i++)
    {
        cout << *(p+i);
    }

    cout<<endl;

    
    p--;
    p+=n;    
    free(p);

    return 0;
}