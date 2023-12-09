#include<iostream>
#include<string>

#define ll long long 
#define ull unsigned long long 

using namespace std;

inline bool legalNumber(string s);
inline bool isPositive(string s);
inline string Clear(string s);
inline string Multiply(string a, string b);
//zhe me hao wan de?
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
        
    string a = "", b = "";
    while(a != "E"){
        string result = "";
        
        cout << "Please input two integers, space for seperation. Enter E to exit." << endl;
        input: cin >> a;
        if(a == "E") break;
        cin >> b;
        
        //first check whether the two inputs are number
        if(!legalNumber(a) | !legalNumber(b)) {
            cout << "The input is illegal! Please try again or E to exit." << endl;
            goto input;
        }
        
        //second check whether the two number is positive or negative
        if(isPositive(a) ^ isPositive(b)){//xor, when only one of a and b is negative, true and get in.
            result += "-";
        }

        //third delete the front zero and minus
        a = Clear(a);
        b = Clear(b);

        //forth multiply
        if(a == "0" | b == "0") result += "0";
        else result += Multiply(a,b);
    
        cout << result << endl;
    }

    cout << "Thank you for calculating. See you next time." <<endl;
    return 0;
}

bool legalNumber(string s)
{
    if(s[0] == '-' | s[0] == '+'){
        s = s.substr(1);
    }
    int che = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= '0' & s[i] <= '9'){
            che++;
        }
    }
    if(che == s.length()) return true;
    else return false;
}

bool isPositive(string s)
{
    if(s[0]=='-'){
        return false;
    }
    return true;
}

string Clear(string s)
{
    int i = 0;
    for( ; i < s.size(); i++){
        if(s[i] != '0' & s[i] != '-' & s[i] != '+'){
            break;
        }
    }
    if(s.substr(i).length() == 0) return s;
    else return s.substr(i);
}

//multiplication for large numbers, in hand calculation way
string Multiply(string a, string b)
{
    string result = "";
    int al[1010] = {0};
    int bl[1010] = {0};
    int tmp[2020] = {0};
    int i = 0, j = 0;
    
    for(i = a.length() - 1, j = 0; i >= 0; i--, j++){
        al[j] = a[i] - '0';
    }
    for(i = b.length() - 1, j = 0; i >= 0; i--, j++){
        bl[j] = b[i] - '0';
    }
    
    //calculate
    for(i = 0; i < a.length(); i++){
        for(j = 0; j < b.length(); j++){
            tmp[i + j] += al[i] * bl[j];
        }
    }
    
    //carry
    for(i = 0; i < (a.length() + b.length()); i++){
        if(tmp[i] > 9){
            tmp[i+1] += tmp[i]/10;
            tmp[i] %= 10; 
        }
    }
    
    for(i = a.length() + b.length(); i >= 0 ; i--){
        if(tmp[i] == 0) continue;
        else break;
    }
    
    for(; i >=0; i--) result += to_string(tmp[i]);
    return result;
}
 