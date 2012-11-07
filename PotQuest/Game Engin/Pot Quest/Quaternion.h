#pragma once
#include "Matrix33.h"
#include "Properties.h"

class Quaternion: public Matrix33{
public:
	Quaternion();
	Quaternion(float, float, float, float);
	Quaternion mult(Quaternion, Quaternion);
	void normalize();
	float dot(Quaternion);
	Quaternion sub(Quaternion);
	
	Quaternion rotateAround(Vector3, float);//axis, radians
	Quaternion lerp(Quaternion q1, Quaternion q2, float time);

	Quaternion operator* (Quaternion& v);
	Quaternion operator* (float& v);
	Quaternion operator+ (Quaternion& v);
	bool operator==(const Quaternion& other);
	bool operator!=(const Quaternion& other);
	Quaternion& operator=(const Quaternion& other);

	float length();
	void inverse();

	~Quaternion(void);
	float w,x,y,z;
};

