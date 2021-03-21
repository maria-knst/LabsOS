#include <math.h>
#include "framework.h"
#include "MyDll.h"
#include"..//Project1/MyStatLib.h"


// Пример экспортированной переменной
MYDLL_API int nMyDll = 13;


MyDllVector::MyDllVector()
{
    this->x = 0;
    this->y = 0;
}

MyDllVector::MyDllVector(MyStatLib::Number x_, MyStatLib::Number y_) {
    this->x = x_;
    this->y = y_;
}

MyDllVector::MyDllVector(const MyDllVector& vector) {
    this->x = vector.x;
    this->y = vector.y;
}


MyStatLib::Number MyDllVector::GetX()
{
    return this->x;
}

MyStatLib::Number MyDllVector::GetY() {
    return this->y;
}

MyDllVector MyDllVector::plus(const MyDllVector& first, const MyDllVector& second) {
    MyStatLib::Number f;
    MyStatLib::Number s;
    f = MyStatLib::Number::plus(first.x,second.x);
    s = MyStatLib::Number::plus(first.y, second.y);

    MyDllVector v(f, s);
    return v;
}

MyDllVector MyDllVector::minus(const MyDllVector& first, const MyDllVector& second) {
    MyStatLib::Number f;
    MyStatLib::Number s;
    f = MyStatLib::Number::difference(first.x, second.x);
    s = MyStatLib::Number::difference(first.y, second.y);

    MyDllVector v(f, s);
    return v;
}

MyStatLib::Number MyDllVector::GetPolarDistance() {
    MyStatLib::Number r(sqrt(this->GetX().GetValue()+ this->GetY().GetValue()));

    return r;
}

MyStatLib::Number MyDllVector::GetPolarAngle() {
    MyStatLib::Number a(atan((this->GetY().GetValue()) / (this->GetX().GetValue())));
    return a;
}
