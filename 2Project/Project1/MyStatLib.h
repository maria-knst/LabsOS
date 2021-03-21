#pragma once

namespace MyStatLib {

	class Number {

	public:

		Number();
		Number(double value);
		Number(const Number& number);
		double GetValue();

		static Number plus(const Number& firstNumber, const Number& secondNumber);
		static Number difference(const Number& firstNumber, const Number& secondNumber);
		static Number multipl(const Number& firstNumber, const Number& secondNumber);
		static Number division(const Number& firstNumber, const Number& secondNumber);

	    Number& operator+=(const Number& other);
		Number& operator-=(const Number& other);
		Number& operator *=(const Number& other);
		Number& operator /=(const Number& other);
		Number& operator=(const Number& other);

	private:
		double value_;
	};
}
