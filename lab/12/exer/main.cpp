#include "CStereoShape.hpp"

int main()
{
    CCube a_cube(4.0, 5.0, 6.0);
    CSphere c_sphere(7.9);
    CStereoShape * p = new CCube(a_cube);
    p->show();
}