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
	Matrix(double theta, int _row = 4, int _column = 4);
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

// constructor with theta
template<class T>
Matrix<T>::Matrix(double theta, int _row, int _column)
	: row_(_row), column_(_column)
{
	const double PI = 3.14159265358979323846;
	const double theta_rad = theta / 180.0 * PI;
	const double cos_theta = cos(theta_rad);
	const double sin_theta = sin(theta_rad);

	values_ = new T*[row_];

	for (int i = 0; i < row_; ++i)
	{
		values_[i] = new T[column_];

		for (int j = 0; j < column_; ++j)
		{
			values_[i][j] = 0;
		}
	}

	values_[0][0] = cos_theta;
	values_[0][1] = -sin_theta;
	values_[1][0] = sin_theta;
	values_[1][1] = cos_theta;
	values_[2][2] = 1;
	values_[3][3] = 1;
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
	// column of matrix and size of vector must be same
	assert(column_ == _v.size());

	// size of output vector should be row of matrix
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
	// column of matrix1 and row of matrix2 must be same
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