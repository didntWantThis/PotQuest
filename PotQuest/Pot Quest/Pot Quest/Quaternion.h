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

	Quaternion getConjugate()
	{
		return Quaternion(-x, -y, -z, w);
	}

	Matrix4 Quaternion::getMatrix() const
	{
		float x2 = x * x;
		float y2 = y * y;
		float z2 = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;

		// This calculation would be a lot more complicated for non-unit length quaternions
		// Note: The constructor of Matrix4 expects the Matrix in column-major format like expected by
		//   OpenGL
		return Matrix4( 1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
			2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	float length();
	void inverse();

	~Quaternion(void);
	float w,x,y,z;
};

