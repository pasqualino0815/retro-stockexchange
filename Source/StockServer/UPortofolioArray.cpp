//---------------------------------------------------------------------------


#pragma hdrstop

#include "UPortofolioArray.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TPArray::TPArray() {
	size = 0;
}

TPArray::~TPArray() {
	Clear();
}

void TPArray::Delete(int index) {
	if(index < size && index > -1) {
		arr[index]->~TPortofolio();
		int i;
		for(i=index;i < size - 1;i++) {
			arr[i] = arr[i+1];
		}
		size--;
	}
}

void TPArray::Add(TPortofolio *porto) {
	if(size < MAXSIZE) {
		arr[size] = porto;
		size++;
  }
}
void TPArray::Clear() {
	int i;
	for(i=0;i<size;i++) {
		arr[i]->~TPortofolio();
  }
}

int TPArray::Count() {
  return size;
}

TPortofolio* TPArray::operator [](int index) {
	if(index < MAXSIZE && index > -1)
		return arr[index];
	else
		return 0;
}
