#include <iostream>
using namespace std;

void displaySquare(int side = 4, char filledCharacter = '*');

int main(){
    int side;
    char fc;
    cout<<"Plaese input the side and the filled character."<<endl;
    cin>>side>>fc;
    displaySquare(side, fc);
    displaySquare();
}

void displaySquare(int side, char filledCharacter){
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            cout << filledCharacter; 
        }
        cout<<endl;
    }
}