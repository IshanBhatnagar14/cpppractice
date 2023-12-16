/*
 * File: opoverload.cpp
 * Project: practice
 * File Created: Sunday, 10th July 2022 11:39:53 pm
 * Author: Ishan B (ishan.b@octobotics.tech)
 * -----
 * Last Modified: Monday, 11th July 2022 2:07:03 am
 * Modified By: Ishan B (ishan.b@octobotics.tech)
 * -----
 * Copyright 2022 - 2022 @Octobotics Tech, Octobotics Tech Pvt Ltd
 */

#include <cstdio>
#include <iostream>
class Complex {
    int real ;
    int imag ;

public:

Complex(int r , int i ): real(r),imag(i) {}

Complex(const Complex &rhs):real(rhs.real),imag(rhs.imag){}  // Copy Constructor 

Complex operator + (const Complex & );


};

Complex::operator+ (const Complex &rhs)  {
    return Complex((this->real + rhs.real),(this->imag+ rhs.imag));
}



int main()
{
    Complex c1(2,3);
    Complex c2 (7,9);

    Complex c3 = c1 + c2;

    std::cout<<c3 << std::endl;
    
}