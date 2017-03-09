#pragma once
#include <iostream>
#include <cassert>
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

template<class T>
T dotProduct(Vector<T>& v1, Vector<T>& v2)
{
	// v1 and v2's size must be same
	assert(v1.size() == v2.size());

	T result = 0;

	for (int i = 0; i < v1.size(); ++i)
	{
		result += v1.values_[i] * v2.values_[i];
	}

	return result;
}