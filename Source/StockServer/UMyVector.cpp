//---------------------------------------------------------------------------

template<class T>
void MyVector<T>::Add(T t) {
	push_back(t);
}
template<class T>
void MyVector<T>::Delete(int index) {
	erase(begin()+index,begin()+index+1);
}
template<class T>
int MyVector<T>::Count() {
	return size();
}
template<class T>
int MyVector<T>::IndexOf(T t) {
	int i;
	for(i=0;i<size();i++) {
		if(this->at(i) == t)
			return i;
	}
	return -1;
}

/*template<>
void MyVector<AnsiString>::Add(AnsiString t) {
	push_back(t);
}
template<>
void MyVector<AnsiString>::Delete(int index) {
	erase(begin()+index,begin()+index+1);
}
template<>
int MyVector<AnsiString>::Count() {
	return size();
}
template<>
int MyVector<AnsiString>::IndexOf(AnsiString t) {
	int i;
	for(i=0;i<size();i++) {
		if(this->at(i) == t)
			return i;
	}
	return -1;
}      */




//---------------------------------------------------------------------------


