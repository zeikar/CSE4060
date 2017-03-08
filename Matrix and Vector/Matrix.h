#pragma once
#include <iostream>
#include <cassert>
#include "Vector.h"
using namespace std;

template<class T>
class Matrix
{
public:
	T **values_;

	Matrix(int _row = 3, int _column = 3);
	Matrix(const Matrix& m);
	~Matrix();

	//friend ostream& operator<<(ostream& os, const Matrix<TT>& m);
	void print();
	const int row();
	const int column();

	Vector<T> multiply(Vector<T>& _v);
	Matrix<T> multiply(Matrix<T>& _m);

private:
	int row_, column_;
};

template<class T>
Matrix<T>::Matrix(int _row, int _column)
	: row_(_row), column_(_column)
{
	values_ = new T*[row_];

	for (int i = 0; i < row_; ++i)
	{
		values_[i] = new T[column_];

		for (int j = 0; j < column_; ++j)
		{
			values_[i][j] = 0;
		}
	}
}

template<class T>
Matrix<T>::Matrix(const Matrix & m)
	: row_(m.row_), column_(m.column_)
{
	values_ = new T*[row_];

	for (int i = 0; i < row_; ++i)
	{
		values_[i] = new T[column_];

		for (int j = 0; j < column_; ++j)
		{
			values_[i][j] = m.values_[i][j];
		}
	}
}

template<class T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < row_; ++i)
	{
		delete[] values_[i];
	}
	delete[] values_;
}

template<class T>
void Matrix<T>::print()
{
	cout << "Matrix " << row_ << "X" << column_ << endl;

	for (int i = 0; i < row_; ++i)
	{
		for (int j = 0; j < column_; ++j)
		{
			cout << values_[i][j] << ' ';
		}
		cout << '\n';
	}
}

template<class T>
inline const int Matrix<T>::row()
{
	return row_;
}

template<class T>
inline const int Matrix<T>::column()
{
	return column_;
}

template<class T>
Vector<T> Matrix<T>::multiply(Vector<T>& _v)
{
	// cant operate 
	assert(column_ == _v.size());

	Vector<T> output_v(row_);

	for (int i = 0; i < row_; i++)
	{
		for (int j = 0; j < column_; j++)
		{
			output_v.values_[i] += values_[i][j] * _v.values_[j];
		}
	}

	return output_v;
}

template<class T>
Matrix<T> Matrix<T>::multiply(Matrix<T>& _m)
{
	// cant operate 
	assert(column_ == _m.row_);
	
	Matrix<T> output_m(row_, _m.column_);

	for (int i = 0; i < row_; i++)
	{
		for (int j = 0; j < _m.column_; j++)
		{
			for (int k = 0; k < column_; k++)
			{
				output_m.values_[i][j] += values_[i][k] * _m.values_[k][j];
			}
		}
	}

	return output_m;
}
