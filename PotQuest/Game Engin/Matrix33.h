#include "Properties.h"
#pragma once
class Matrix33
{
public:
	Matrix33(void);
	void set(int, int, int);
	float get(int, int);
	void print();

	Vector3 multVectors(Vector3, Matrix33);
	Matrix33 multMatrix(Matrix33, Matrix33);

	~Matrix33(void);
private:
	float mV[9];
};

	