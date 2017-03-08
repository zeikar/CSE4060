#pragma once
#include <iostream>
using namespace std;

template<class T>
class Vector
{
public:
	T *values_;

	Vector(int _size = 3);
	Vector(const Vector& v);
	~Vector();

	void print();
	const int size();

private:	
	int size_;
};

template<class T>
Vector<T>::Vector(int _size)
	: size_(_size)
{
	values_ = new T[size_];

	for (int i = 0; i < size_; ++i)
	{
		values_[i] = 0;
	}
}

template<class T>
Vector<T>::Vector(const Vector & v)
	:size_(v.size_)
{
	values_ = new T[v.size_];

	for (int i = 0; i < size_; ++i)
	{
		values_[i] = v.values_[i];
	}
}

template<class T>
Vector<T>::~Vector()
{
	delete[] values_;
}

template<class T>
void Vector<T>::print()
{
	cout << "Vector " << size_ << "D" << endl;

	for (int i = 0; i < size_; ++i)
	{
		cout << values_[i] << ' ';
	}
	cout << endl;
}

template<class T>
const int Vector<T>::size()
{
	return size_;
}
