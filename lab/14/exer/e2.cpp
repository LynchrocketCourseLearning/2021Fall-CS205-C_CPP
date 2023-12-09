#include<iostream>
#include<cassert>
using namespace std;

class OutOfRangeException
{
    private:
        int code;
        int val;
    public:
        OutOfRangeException(int c,int v):code(c),val(v){};
        const char* what(){
            static char s[100];
            snprintf(s,100,"The parameter %d is %d which is out of range (0-100).", code, val);
            return s;
        }
};

float calculateAverage(int a, int b, int c, int d)
{
    assert(a < 0 || a > 100);
    assert(b < 0 || b > 100);
    assert(c < 0 || c > 100);
    assert(d < 0 || d > 100);
    float res = (float)(a+b+c+d)/4; 
    return res;
}

int main()
{
    do{
        cout << "Please enter marks for 4 courses: ";
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        float res;
        bool che = 0;
        try
        {
            res = calculateAverage(a,b,c,d);
        }
        catch(OutOfRangeException& e)
        {
            che = 1;
            cout << e.what() << '\n';
        }
        if(!che) cout << "The average of the 4 courses is " << res << '\n';
        char in;
        cout << "Would you want to enter another marks for 4 courses(y/n)? ";
        cin >> in;
        if(in == 'n') break;
    }while(1);

    cout << "Bye, see you next time." << '\n';

    return 0;
}