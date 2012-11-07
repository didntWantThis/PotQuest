#pragma once
#include "Includes.h"

class Vertex
{
public:
	//similar to normals class
	//makes a vector
	float x,y,z;
	float magnitude;
	float distance;
	Vertex()
	{
		x=y=z=0;
	}
	~Vertex(){}
	//literally an empty class
	float Magnitude()
	{
		return sqrtf(x*x+y*y+z*z);
	}


	Vertex(float x1, float y1, float z1)
	{
		this->x =x1;
		this->y = y1;
		this->z = z1;
	}

	void Normalize()
	{
		magnitude = this->Magnitude();
		x/=magnitude;
		y/=magnitude;
		z/=magnitude;
	}

	float Distance(float _x, float _y, float _z)
	{

		return sqrtf(powf(_x-this->x,2) - powf(_y-this->y,2) - powf(_z - this->z,2));
	}

};

class Face
{
public:
	std::vector<int> texture,normals,vertices, boundingfaces;

	Face(){}; //does  :nothing
	~Face(){}

};

class Texture
{
public:
	//holds the texture co-ordinates of the object
	float u,v;
	Texture (float _u, float _v)
	{
		this->u = _u;
		this->v = _v;
	}

	Texture()
	{
		u=v=0;
	}
};

class Normals
{
public:
	//Normals file
	//used for lighting
	//very important
	float x,y,z; //nearly all of these will have this
	//is a normal vector
	Normals(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Normals()
	{
		x=y=z=0;
	}
};

class Vector3{
public:
	float x,y,z;

	Vector3(void){x=y=z=0;};

	Vector3(float x,float y,float z){
		this->x=x;
		this->y=y;
		this->z=z;
	}

	void setX(double pX){x = pX;};
	void setY(double pY){y = pY;};
	void setZ(double pZ){z = pZ;};
	float getX(){ return x; };
	float getY(){ return y; };
	float getZ(){ return z; };

	float getMagnatude(){
		float magnitude = sqrt(x*x+y*y+z*z);
		return magnitude;
	}

	Vector3 normalize (){
		float length = this->getMagnatude();
		Vector3 temp;
		temp.setX(this->getX()/length);
        temp.setY(this->getY()/length);
        temp.setZ(this->getZ()/length);
		return temp;
	}

	float dotProduct (Vector3 *vec){
		Vector3 temp;
		float ret;
		temp.x = this->x * vec->x;
		temp.y = this->y * vec->y;
		temp.z = this->z * vec->z;
		ret = temp.x+temp.y+temp.z;
		return ret;
	}

	Vector3 crossProduct(Vector3 *vec){
		Vector3 temp;
		temp.x = (this->y*vec->z) - (this->z*vec->y);
		temp.y = (this->z*vec->x) - (this->x*vec->z);
		temp.z = (this->x*vec->y) - (this->y*vec->x);
		return temp;
	}

	//overloading

	//add two vectors
	Vector3 operator+(const Vector3 &vec) const{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3 operator-(const Vector3 &vec) const{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 operator*(float num) const{
		return Vector3(x * num, y * num, z * num);
	}

	friend Vector3 operator*(float num, Vector3 const &vec){
		return Vector3(vec.x * num, vec.y * num, vec.z * num);
	}
};

