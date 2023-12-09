#include"matrix.hpp"

int main()
{
    Matrix a(3,4,3.5);
    Matrix b(3,4,4.2);

    a.show();
    b.show();

    Matrix c = a + b;
    c.show();

    Matrix d = c;
    d.show();
    d = a * 2.0f;
    d.show();

    return 0;
}
