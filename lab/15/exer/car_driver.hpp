#pragma once
#include <iostream>
#include <cstdio>
using namespace std;

class Car
{
    private:
        enum {Off, On};
        enum {Minvel, Maxvel = 200};
        int mode;
        int velocity;
    public:
        friend class Driver;
        Car(int m = On, int v = 50):mode(m),velocity(v){}
        bool velup(int v);
        bool veldown(int v);
        bool isOn() const;
        int getVel() const;
        void showInfo() const;
};

class Driver
{
    public:
        bool velup(Car& car, int v);
        bool veldown(Car& car, int v);
        void setmode(Car& car);
        bool isOn(Car& car) const;
};

bool Car::velup(int v)
{
    this->velocity += v;
    if(this->velocity > Maxvel)
    {
        printf("Increase velocity by car. The velocity is %d. It is out of Maxvel.\n", this->velocity);
    }
    return true;
}
bool Car::veldown(int v)
{
    if(this->velocity - v < Minvel)
    {
        printf("Decrease velocity by car. The velocity %d now is too low to slow down.\n", this->velocity);
    } 
    else 
    {
        this->velocity -= v;
        printf("Increase velocity by car. The velocity is %d.\n", this->velocity);
    }
    return true;
}
bool Car::isOn() const
{
    return (this->mode==On);
}
int Car::getVel() const
{
    return this->velocity;
}
void Car::showInfo() const
{
    printf("The information of car: mode is %d, velocity is %d.\n", this->mode, this->velocity);
} 

bool Driver::velup(Car& car, int v)
{
    car.velocity += v;
    if(car.velocity > Car::Maxvel)
    {
        printf("Increase velocity by driver. The velocity is %d. It is out of Maxvel.\n", car.velocity);
    }
    return true;
}
bool Driver::veldown(Car& car, int v)
{
    if(car.velocity - v < Car::Minvel)
    {
        printf("Decrease velocity by driver. The velocity %d now is too low to slow down.\n", car.velocity);
    } 
    else 
    {
        car.velocity -= v;
        printf("Increase velocity by driver. The velocity is %d.\n", car.velocity);
    }
    return true;
}
void Driver::setmode(Car& car)
{
    printf("Set the mode of car by driver.\n");
    (car.mode==1)?car.mode=0:car.mode=1;
    printf("The mode of car is: %d\n", car.mode);
}
bool Driver::isOn(Car& car) const
{
    return (car.mode==1);
}