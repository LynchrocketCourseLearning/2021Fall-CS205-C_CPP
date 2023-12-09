#include <iostream>
using namespace std;

int main()
{
    bool che = 0;
    do {
    char op;
    cout << "Please select an operation:" << endl;
    printf("+\n-\n*\n/\n");
    cin >> op;

    int a = 0, b = 0;
    cout << "Please input two integers:" << endl;
    cin >> a >> b;
    
    int result = 0;
    switch (op){
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if(b==0){
                cout << "The dividend can not be 0, please input the dividend again." << endl;
                cin >> b;
            }
            result = a / b; break;
    }
    printf("%d %c %d = %d\n",a,op,b,result);

    che = 0;
    char test;
    cout << "Do you want to continue? (Y/N)";
    cin >> test;

    if(test == 'Y' || test == 'y') che = 1;

    }while(che);

    cout << "The operator is over.";


    return 0;
}