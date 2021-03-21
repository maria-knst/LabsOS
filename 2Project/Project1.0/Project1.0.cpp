
#include <iostream>
#include"..//MyDll/MyDll.h"
#include"MyStatLib.h"

int main()
{
    std::cout << "Hello World!\n";

    MyStatLib::Number r(2);
    MyStatLib::Number l(10);

    std::cout << r.GetValue() << "\t" << l.GetValue() << "\n";
    std::cout << MyStatLib::Number::plus(r, l).GetValue() << std::endl;
    std::cout << MyStatLib::Number::difference(l,r).GetValue() << std::endl;
    std::cout << MyStatLib::Number::division(l,r).GetValue() << std::endl;
    std::cout << MyStatLib::Number::multipl(l, r).GetValue() << std::endl;

    MyDllVector v1(1, 2);
    MyDllVector v2(2, 1);
    
    std::cout << v1.GetX().GetValue() << "\n";
    std::cout << v1.GetPolarDistance().GetValue() << "\n";
    std::cout << v1.GetPolarAngle().GetValue();

    return 0;
}

