#include"MyStatLib.h"

namespace MyStatLib {

	Number::Number() {
		value_ = 0;
	}
	Number::Number(double value) {
		value_ = value;
	}
	Number::Number(const Number& number) {
		value_ = number.value_;
	}
	double Number::GetValue() { return value_; }


	Number Number::plus(const Number& firstNumber, const Number& secondNumber) {

		Number sum = firstNumber;
		sum += secondNumber;

		return sum;
	}

	Number Number::difference(const Number& firstNumber, const Number& secondNumber) {
		Number dif = firstNumber;
		dif -= secondNumber;

		return dif;
	}

	Number Number::multipl(const Number& firstNumber, const Number& secondNumber) {

		Number mult = firstNumber;
		mult *= secondNumber;

		return mult;
	}

	Number Number::division(const Number& firstNumber, const Number& secondNumber) {

		Number div = firstNumber;
		div /= secondNumber;

		return div;
	}

	Number& Number::operator+=(const Number& other) {
		value_ = value_ + other.value_;
		return *this;
	}

	Number& Number::operator-=(const Number& other) {
		value_ = value_ - other.value_;
		return *this;
	}

	Number& Number::operator*=(const Number& other) {
		value_ = value_ * other.value_;
		return *this;
	}

	Number& Number::operator/=(const Number& other) { 
		if (other.value_ != 0) {
			value_ = value_ / other.value_;
		}
		return *this;
	}

	Number& Number::operator=(const Number& other) {
		if (this == &other) {
			return *this;
		}

		value_ = other.value_;
		return *this;
	}


}