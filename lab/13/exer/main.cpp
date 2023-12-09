#include <iostream>
#include "Matrix.cpp"

int main()
{
    Matrix<float> ma(3,3);
    ma(1,2,3);
    ma(2,2,5);
    ma.print();
    std::cout<<std::endl;

    Matrix<float> mb(3,3);
    mb(1,2,3);
    mb(2,2,5);
    mb.print();
    std::cout<<std::endl;

    Matrix<float> mc(3,3); 
    mc = ma + mb;
    mc.print();
    std::cout<<std::endl;

    Matrix<float> md(3,3);     
    md = ma * mb;
    md.print();


    return 0;
}