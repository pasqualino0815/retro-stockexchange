//---------------------------------------------------------------------------

#ifndef UMyVectorH
#define UMyVectorH

#include <vector>

template<class T>
class MyVector : public std::vector<T> {
public:
	void Add(T t);
	void Delete(int index);
	int IndexOf(T t);
	int Count();
};

#include "UMyVector.cpp"

//---------------------------------------------------------------------------
#endif
