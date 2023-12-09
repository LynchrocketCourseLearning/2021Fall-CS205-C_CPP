#include "car_driver.hpp"

int main()
{
    Car car(1,10);
    Driver driver;
    car.showInfo();
    car.velup(100);
    car.velup(100);
    car.veldown(20);
    driver.setmode(car);

    return 0;
}