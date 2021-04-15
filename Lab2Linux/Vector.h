#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include "Number.h"


class Vector {
public:
	MyStatLib::Number x;
	MyStatLib::Number y;

	Vector();
	Vector(MyStatLib::Number x_, MyStatLib::Number y_);
	Vector(const Vector& vector);

	MyStatLib::Number GetX();
	MyStatLib::Number GetY();
	Vector plus(const Vector& first, const Vector& second);
	Vector minus(const Vector& first, const Vector& second);

	MyStatLib::Number GetPolarDistance();
	MyStatLib::Number GetPolarAngle();


};

#endif //VECTOR_VECTOR_H
