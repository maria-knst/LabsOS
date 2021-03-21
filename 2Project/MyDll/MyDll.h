
#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

#include"..//Project1/MyStatLib.h"

class MYDLL_API MyDllVector {
public:
	MyStatLib::Number x;
	MyStatLib::Number y;

	MyDllVector();
	MyDllVector(MyStatLib::Number x_, MyStatLib::Number y_);
	MyDllVector(const MyDllVector& vector);

	MyStatLib::Number GetX();
	MyStatLib::Number GetY();
	MyDllVector plus(const MyDllVector& first, const MyDllVector& second);
	MyDllVector minus(const MyDllVector& first, const MyDllVector& second);

	MyStatLib::Number GetPolarDistance();
	MyStatLib::Number GetPolarAngle();


};

extern MYDLL_API int nMyDll;

