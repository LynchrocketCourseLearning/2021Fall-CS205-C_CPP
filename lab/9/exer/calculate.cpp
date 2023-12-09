#include<cstdio>
using namespace std;

class Complex
{
private:
    double real;
    double imag;
public:
Complex();
    Complex(double real, double imag);
    ~Complex();
    void add(Complex &b);
    void subtract(Complex &b);
    void display() const;
};

Complex::Complex()
{
    this->real = 0;
    this->imag = 0;
}

Complex::Complex(double real, double imag)
{
    this->real = real;
    this->imag = imag;
}

Complex::~Complex()
{
}

void Complex::add(Complex &b){
    this->real += b.real;
    this->imag += b.imag;
}
void Complex::subtract(Complex &b){
    this->real -= b.real;
    this->imag -= b.imag;
}

void Complex::display() const{
    if(this->imag > 0)
        printf("%.2lf + %.2lfi\n",this->real,this->imag);
    if(this->imag < 0)
        printf("%.2lf - %.2lfi\n",this->real,-this->imag);
    if(this->imag == 0)
        printf("%.2lf\n",this->real);
}

int main(){
    printf("input 4 double numbers.\n");
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    Complex num1 = Complex(a, b);
    Complex num2 = Complex(c, d);
    Complex num3; 

    num1.display();
    num2.display();
    num3.display();

    num1.add(num2);
    num2.subtract(num1);
    num3.add(num1);
        
    num1.display();
    num2.display();
    num3.display();

    return 0;
}