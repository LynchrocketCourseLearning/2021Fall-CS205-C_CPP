#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>

class CStereoShape
{
private:
    static size_t numOfObject;
public:
    CStereoShape();
    CStereoShape(const CStereoShape &);
    ~CStereoShape();
    size_t getNumOfObject();
    virtual double getArea();
    virtual double getVolume();
    virtual void show();
};

size_t CStereoShape::numOfObject = 0;

CStereoShape::CStereoShape()
{
    this->numOfObject++;
}

CStereoShape::CStereoShape(const CStereoShape &a)
{
}

CStereoShape::~CStereoShape()
{
}

size_t CStereoShape::getNumOfObject()
{
    return this->numOfObject;
}

double CStereoShape::getArea()
{
    printf("CStereoShape::getArea()\n");
    return 0.0;
}

double CStereoShape::getVolume()
{
    printf("CStereoShape::getVolume()\n");
    return 0.0;
}

void CStereoShape::show()
{
    printf("CStereoShape::show()\n");
}

class CCube:public CStereoShape
{
private:
    double length;
    double width;
    double height;
public:
    CCube():length(0),width(0),height(0){};
    CCube(double l,double w,double h):length(l),width(w),height(h){};
    CCube(const CCube &);
    ~CCube();

    double getArea();
    double getVolume();
    void show();
};

CCube::CCube(const CCube &a):CStereoShape(a)
{
    this->length = a.length;
    this->width = a.width;
    this->height = a.height;
}

CCube::~CCube()
{
}

double CCube::getArea()
{
    return 2*(this->length*this->width+this->length*this->height+this->width*this->height);
}

double CCube::getVolume()
{
    return this->length*this->width*this->height;
}

void CCube::show()
{
    printf("Cube Length = %.2f, Width = %.2f, Height = %.2f, Surface area = %.2f, Volume = %.2f\n",this->length,this->width,this->height,this->getArea(),this->getVolume());
    printf("number of object:%ld\n",this->getNumOfObject());
}

class CSphere:public CStereoShape
{
private:
    double radius;
public:
    CSphere():radius(0){};
    CSphere(double ra):radius(ra){};
    CSphere(const CSphere &);
    ~CSphere();

    double getArea();
    double getVolume();
    void show();
};

CSphere::CSphere(const CSphere &a)
{
    this->radius = a.radius;
}

CSphere::~CSphere()
{
}

double CSphere::getArea()
{
    return M_PI * this->radius * this->radius;
}

double CSphere::getVolume()
{
    return 4.0 * M_PI * this->radius * this->radius * this->radius / 3.0;
}

void CSphere::show()
{
    printf("Sphere Radius = %.2f, Surface area = %.2f, Volume = %.2f\n",this->radius,this->getArea(),this->getVolume());
    printf("number of object:%ld\n",this->getNumOfObject());
}
