#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion(){
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	w = _w;
	x = _x;
	y = _y; 
	z = _z;

}

void Quaternion::normalize(){
	float divisor = sqrt(w*w + x*x + y*y + z*z);
		
	w /= divisor;
	x /= divisor;
	y /= divisor;
	z /= divisor;
}

float Quaternion::dot(Quaternion otherQuat)
{
	return w*otherQuat.w + x*otherQuat.x + y*otherQuat.y + z*otherQuat.z;
}

Quaternion Quaternion::sub(Quaternion quat){
	Quaternion result(0,0,0,0);
	result.w = w-quat.w;
	result.x = x-quat.x;
	result.y = y-quat.y;
	result.z = z-quat.z;
	return result;
}

Quaternion::~Quaternion(void)
{
}

Quaternion Quaternion::lerp(Quaternion q1, Quaternion q2, float time)
{
	float scale = 1.0f - time;
	return (*this = (q1*scale) + (q2*time));
}

Quaternion Quaternion::operator* (Quaternion& quat)
{
	Quaternion result(0,0,0,0);
	result.w = w*quat.w - x*quat.x - y*quat.y - z*quat.z;
	result.x = w*quat.x + x*quat.w + y*quat.z - z*quat.y;
	result.y = w*quat.y - x*quat.z + y*quat.w + z*quat.x;	
	result.z = w*quat.z + x*quat.y - y*quat.x + z*quat.w;

	return result;
}

Quaternion Quaternion::operator+ (Quaternion& b){
	return Quaternion(w+b.w, x+b.x, y+b.y, z+b.z);
}

Quaternion Quaternion::operator* (float& s){
	return Quaternion(s*w, s*x, s*y, s*z);
}

// equal operator
bool Quaternion::operator==(const Quaternion& other){
	return ((x == other.x) &&
		(y == other.y) &&
		(z == other.z) &&
		(w == other.w));
}

// inequality operator
bool Quaternion::operator!=(const Quaternion& other)
{
	return !(*this == other);
}

// assignment operator
Quaternion& Quaternion::operator=(const Quaternion& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}
