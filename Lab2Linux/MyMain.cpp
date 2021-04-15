#include<iostream>
#include"Vector.h"
#include"Number.h"

using namespace MyStatLib;

int main(){

auto x = Number(12);
auto y = Number(8);

std::cout << "x: " << x.GetValue() << " y: " << y.GetValue() << "\n";

std::cout << " y+x = " << Number::plus(x,y).GetValue() << " y-x =  " << Number::difference(y,x).GetValue() << "\n";

auto v1 = Vector(1,2);
auto v2 = Vector(2,1);

std::cout << "v1: " << v1.GetX().GetValue() << " " << v1.GetY().GetValue() << " \n";
std::cout << "v2: " << v2.GetX().GetValue() << " " << v2.GetY().GetValue() << " \n";

std::cout<< v1.GetPolarDistance().GetValue() << "\n";
std::cout<< v2.GetPolarAngle().GetValue()<< "\n";

  return 0;
}
