#pragma once

#ifndef NUMBER_NUMBER_H
#define NUMBER_NUMBER_H

namespace MyStatLib {

    class Number {

    public:

        Number();
        Number(double value);
        Number(const Number& number);
        double GetValue();
        
        Number operator+=(const Number& other);
        Number operator-=(const Number& other);
        Number operator *=(const Number& other);
        Number operator /=(const Number& other);
        Number& operator=(const Number& other);

        static MyStatLib::Number plus(const Number& firstNumber, const Number& secondNumber);
        static MyStatLib::Number difference(const Number& firstNumber, const Number& secondNumber);
        static MyStatLib::Number multipl(const Number& firstNumber, const Number& secondNumber);
        static MyStatLib::Number division(const Number& firstNumber, const Number& secondNumber);

    private:
        double value_;
    };
}

#endif //NUMBER_NUMBER_H

