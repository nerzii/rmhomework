#include"/home/aolianko/homework01/include/Angle.hpp"
#include<cmath>
#include<iostream>
Angle::Angle():v0(10),g(9.8){};
void Angle::solver(const double d)
{   
    if (0<d<=(std::pow(v0,2)/g))
    {
    double a = std::asin(g*d/std::pow(v0,2))/2;   
    double b = a*(180/M_PI);                
    std::cout << "角度为" << b << std::endl;
    std::cout << "弧度为" << a << std::endl;
    }
    else
    {
    std::cout<<"此题无解哦"<<std::endl;
    }
}


