#include "Number.h"
#include <iostream>


    MyStatLib::Number::Number() {
        value_ = 0;
    }
    MyStatLib::Number::Number(double value) {
        value_ = value;
    }
    MyStatLib::Number::Number(const MyStatLib::Number& number) {
        value_ = number.value_;
    }
    double MyStatLib::Number::GetValue() { return value_; }


    MyStatLib::Number MyStatLib::Number::plus(const MyStatLib::Number& firstNumber, const MyStatLib::Number& secondNumber) {

        MyStatLib::Number sum = firstNumber;
        sum += secondNumber;

        return sum;
    }

    MyStatLib::Number MyStatLib::Number::difference(const MyStatLib::Number& firstNumber, const MyStatLib::Number& secondNumber) {
        MyStatLib::Number dif = firstNumber;
        dif -= secondNumber;

        return dif;
    }

    MyStatLib::Number MyStatLib::Number::multipl(const MyStatLib::Number& firstNumber, const MyStatLib::Number& secondNumber) {

        MyStatLib::Number mult = firstNumber;
        mult *= secondNumber;

        return mult;
    }

    MyStatLib::Number MyStatLib::Number::division(const MyStatLib::Number& firstNumber, const MyStatLib::Number& secondNumber) {

        MyStatLib::Number div = firstNumber;
        div /= secondNumber;

        return div;
    }

    MyStatLib::Number MyStatLib::Number::operator+=(const MyStatLib::Number& other) {
        value_ = value_ + other.value_;
        return *this;
    }

    MyStatLib::Number MyStatLib::Number::operator-=(const MyStatLib::Number& other) {
        value_ = value_ - other.value_;
        return *this;
    }

    MyStatLib::Number MyStatLib::Number::operator*=(const MyStatLib::Number& other) {
        value_ = value_ * other.value_;
        return *this;
    }

    MyStatLib::Number MyStatLib::Number::operator/=(const MyStatLib::Number& other) {
        if (other.value_ != 0) {
            value_ = value_ / other.value_;
        }
        return *this;
    }

    MyStatLib::Number& MyStatLib::Number::operator=(const MyStatLib::Number& other) {
        if (this == &other) {
            return *this;
        }

        value_ = other.value_;
        return *this;
    }



