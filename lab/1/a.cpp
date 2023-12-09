#include <iostream>
#include <string>
using namespace std;

bool isNumber(string s)
{
    if(s[0]=='-'){
        s = s.substr(1);
    }
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= '0' & s[i] <= '9'){
            return true;
        }
    }
    return false;
}

int main()
{
    string a = "0";
    cin >> a;
    cout << isNumber(a) << endl;
    return 0;
}