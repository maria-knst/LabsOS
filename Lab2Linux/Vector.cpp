#include "Vector.h"
#include "Number.h"
#include <iostream>
#include<cmath>

using namespace MyStatLib;

Vector::Vector()
{
    this->x = 0;
    this->y = 0;
}

Vector::Vector(MyStatLib::Number x_, MyStatLib::Number y_) {
    this->x = x_;
    this->y = y_;
}

Vector::Vector(const Vector& vector) {
    this->x = vector.x;
    this->y = vector.y;
}


MyStatLib::Number Vector::GetX()
{
    return this->x;
}

MyStatLib::Number Vector::GetY() {
    return this->y;
}

Vector Vector::plus(const Vector& first, const Vector& second) {
    MyStatLib::Number f;
    MyStatLib::Number s;
    f = MyStatLib::Number::plus(first.x,second.x);
    s = MyStatLib::Number::plus(first.y, second.y);

    Vector v(f, s);
    return v;
}

Vector Vector::minus(const Vector& first, const Vector& second) {
    MyStatLib::Number f;
    MyStatLib::Number s;
    f = MyStatLib::Number::difference(first.x, second.x);
    s = MyStatLib::Number::difference(first.y, second.y);

    Vector v(f, s);
    return v;
}

MyStatLib::Number Vector::GetPolarDistance() {
    MyStatLib::Number r(sqrt(this->GetX().GetValue()+ this->GetY().GetValue()));

    return r;
}

MyStatLib::Number Vector::GetPolarAngle() {
    MyStatLib::Number a(atan((this->GetY().GetValue()) / (this->GetX().GetValue())));
    return a;
}

