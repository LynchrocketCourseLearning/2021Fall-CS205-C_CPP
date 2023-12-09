#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

class Complex
{
private:
    double real;
    double imag;
public:
    Complex():real(0), imag(0){};
    Complex(double real, double imag):real(real), imag(imag){};
    ~Complex(){};
    double getReal(){return this->real;}
    double getImag(){return this->imag;}
    Complex operator+(const Complex &);
    Complex operator-(const Complex &);
    Complex operator*(const Complex &);
    Complex& operator=(const Complex &);
    bool operator==(const Complex &);
    bool operator!=(const Complex &);
    friend ostream& operator<<(ostream &, const Complex &);
    friend istream& operator>>(istream &, Complex &);
    void display() const;
};

Complex Complex::operator+(const Complex &b){
    Complex c = Complex(this->real + b.real, this->real + b.real);
    return c;
}

Complex Complex::operator-(const Complex &b){
    Complex c = Complex(this->real - b.real, this->real - b.real);
    return c;
}

Complex Complex::operator*(const Complex &b){
    Complex c = Complex(this->real * b.real - this->imag * b.imag, this->imag * b.real + this->real * b.imag);
    return c;
}

Complex& Complex::operator=(const Complex &b){
    this->real = b.real;
    this->imag = b.imag;
    return *this;
}

bool Complex::operator==(const Complex &b){
    if(this->real == b.real && this->imag == b.imag)
        return true;
    else return false;
}

bool Complex::operator!=(const Complex &b){
    return !(*this == b);
}

ostream& operator<<(ostream &os, const Complex &a){
    string s = to_string(a.real);
    if(a.imag > 0)
        s += "+" + to_string(a.imag) + "i";
    if(a.imag < 0)
        s += "-" + to_string(-a.imag) + "i";
    os << s;
    return os;
}

istream& operator>>(istream &is, Complex &a){
    int re, im;
    char sign, i;
    do{
        is >> re >> sign >> im >> i;
    }while(!((sign == '+' || sign == '-') && i == 'i'));
    a.real = re;
    a.imag = (sign == '+')? im : -im;
    return is;
}

int main(){
    Complex num1, num2, num3;
    cin >> num1;
    cin >> num2;
    cin >> num3;

    cout << num1 << endl;
    cout << num2 << endl;
    cout << num3 << endl;

    num3 = num1 + num2;
    num1 = num3 * num2;
    num2 = num3 - num1;

    if(num3 == num1) cout << "True" << endl;
    else cout << "False" << endl;
    
    cout << num1 << endl;
    cout << num2 << endl;
    cout << num3 << endl;

    return 0;
}