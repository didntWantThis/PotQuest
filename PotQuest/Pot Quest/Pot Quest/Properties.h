#pragma once
#include "Includes.h"

const float PI = 3.14159265f;
const float TO_RAD = PI / 180.0f;

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
		this->x = x1;
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

	float Distance(float _x, float _y, float _z){
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

	void set(float x,float y,float z){
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



class Matrix4 
{
public:
// Data
	float mf[ 16 ];
	
	/*const float PI = 3.14159265f;
	const float TO_RAD = PI / 180.0f;*/

// Functions
	Matrix4(float m1,float m2,float m3,float m4,float m5,float m6,float m7,float m8,
		float m9,float m10,float m11,float m12,float m13,float m14,float m15,float m16)	{
			mf[ 0] =  m1;    mf[ 1] =  m2;      mf[ 2] =  m3;    mf[ 3] =  m4;  
			mf[ 4] =  m5;    mf[ 5] =  m6;      mf[ 6] =  m7;    mf[ 7] =  m8;  
			mf[ 8] =  m9;    mf[ 9] = m10;      mf[10] = m11;    mf[11] = m12;  
			mf[12] = m13;    mf[13] = m14;      mf[14] = m15;    mf[15] = m16;
	}
	Matrix4( const int bIdentity = true )
	{
	 if ( bIdentity ) Identity();
	}

	void Identity( )
	{
	mf[ 0] = 1.0f;    mf[ 1] = 0.0f;      mf[ 2] = 0.0f;    mf[ 3] = 0.0f;  
	mf[ 4] = 0.0f;    mf[ 5] = 1.0f;      mf[ 6] = 0.0f;    mf[ 7] = 0.0f;  
	mf[ 8] = 0.0f;    mf[ 9] = 0.0f;      mf[10] = 1.0f;    mf[11] = 0.0f;  
	mf[12] = 0.0f;    mf[13] = 0.0f;      mf[14] = 0.0f;    mf[15] = 1.0f;
	}

	// Concatenate 2 matrices with the * operator
	Matrix4 operator* (const Matrix4 &InM) const
	{
	Matrix4 Result( 0 );
	for (int i=0;i<16;i+=4)
		{
		for (int j=0;j<4;j++)
			{
			Result.mf[i + j] = mf[ i + 0] * InM.mf[ 0 + j] + mf[ i + 1] * InM.mf[ 4 + j]
				+ mf[ i + 2] * InM.mf[ 8 + j] + mf[ i + 3] * InM.mf[ 12 + j];
			}
		}
	return Result;
	}

	// Use a Matrix4 to transform a 3D point with the * operator
	Vector3 operator* (const Vector3 &Point ) const
	{
	 float x = Point.x*mf[0] + Point.y*mf[4] + Point.z*mf[8]  + mf[12];
	 float y = Point.x*mf[1] + Point.y*mf[5] + Point.z*mf[9]  + mf[13];
	 float z = Point.x*mf[2] + Point.y*mf[6] + Point.z*mf[10] + mf[14]; 
	 return Vector3( x, y, z );
	}

	// Rotate the *this Matrix4 fDegrees counter-clockwise around a single axis( either x, y, or z )
	void Rotate( float fDegrees, int x, int y, int z )
	{
	 Matrix4 Temp;
	 if (x == 1) Temp.RotX( -fDegrees );
	 if (y == 1) Temp.RotY( -fDegrees );
	 if (z == 1) Temp.RotZ( -fDegrees );
	 *this = Temp * (*this);
	}

	void Scale( float sx, float sy, float sz )
	{
	 int x;
	 for (x = 0; x <  4; x++) mf[x]*=sx;
	 for (x = 4; x <  8; x++) mf[x]*=sy;
	 for (x = 8; x < 12; x++) mf[x]*=sz;
	}

	void Translate( const Vector3 &Test )
	{
	for (int j=0;j<4;j++)
		{
		mf[12+j] += Test.x * mf[j] + Test.y * mf[4+j] + Test.z * mf[8+j]; 
		}	 
	}
	
	Vector3 GetTranslate( )
	{
		return Vector3( mf[12], mf[13], mf[14] );
	}
	
	// Zero out the translation part of the Matrix4
	Matrix4 RotationOnly( )
	{
	 Matrix4 Temp = *this;
	 Temp.mf[12] = 0;
	 Temp.mf[13] = 0;
	 Temp.mf[14] = 0;
	 return Temp;
	}

	// Create a rotation Matrix4 for a counter-clockwise rotation of fDegrees around an arbitrary axis(x, y, z)
	void RotateMatrix4( float fDegrees, float x, float y, float z)
	{
	Identity();
	float cosA = cosf(fDegrees*TO_RAD);
	float sinA = sinf(fDegrees*TO_RAD);
	float m = 1.0f - cosA;
	mf[0] = cosA + x*x*m;
	mf[5] = cosA + y*y*m;
	mf[10]= cosA + z*z*m;

	float tmp1 = x*y*m;
	float tmp2 = z*sinA;
	mf[4] = tmp1 + tmp2;
	mf[1] = tmp1 - tmp2;

	tmp1 = x*z*m;
	tmp2 = y*sinA;
	mf[8] = tmp1 - tmp2;
	mf[2] = tmp1 + tmp2;

	tmp1 = y*z*m;
	tmp2 = x*sinA;
	mf[9] = tmp1 + tmp2;
	mf[6] = tmp1 - tmp2;
	}

	// Simple but not robust Matrix4 inversion. (Doesn't work properly if there is a scaling or skewing transformation.)
	Matrix4 InvertSimple()
	{
	Matrix4 R(0);
	R.mf[0]  = mf[0]; 		R.mf[1]  = mf[4];		R.mf[2]  = mf[8];	R.mf[3]  = 0.0f;
	R.mf[4]  = mf[1];		R.mf[5]  = mf[5];		R.mf[6]  = mf[9];	R.mf[7]  = 0.0f;
	R.mf[8]  = mf[2];		R.mf[9]  = mf[6];		R.mf[10] = mf[10];	R.mf[11] = 0.0f;
	R.mf[12] = -(mf[12]*mf[0]) - (mf[13]*mf[1]) - (mf[14]*mf[2]);
	R.mf[13] = -(mf[12]*mf[4]) - (mf[13]*mf[5]) - (mf[14]*mf[6]);
	R.mf[14] = -(mf[12]*mf[8]) - (mf[13]*mf[9]) - (mf[14]*mf[10]);
	R.mf[15] = 1.0f;
	return R;
	}
	
	// Invert for only a rotation, any translation is zeroed out
	Matrix4 InvertRot( )
	{
	 Matrix4 R( 0 );
	 R.mf[0]  = mf[0]; 		R.mf[1]  = mf[4];		R.mf[2]  = mf[8];	R.mf[3]  = 0.0f;
	 R.mf[4]  = mf[1];		R.mf[5]  = mf[5];		R.mf[6]  = mf[9];	R.mf[7]  = 0.0f;
	 R.mf[8]  = mf[2];		R.mf[9]  = mf[6];		R.mf[10] = mf[10];	R.mf[11] = 0.0f;
	 R.mf[12] = 0;			R.mf[13] = 0;			R.mf[14] = 0;		R.mf[15] = 1.0f;
	 return R;
	}	


private:
	// helpers for Rotate
	void RotX(float angle)
        {  
        mf[5]  = cosf(angle*TO_RAD);
        mf[6]  = sinf(angle*TO_RAD);
        mf[9]  = -sinf(angle*TO_RAD);
        mf[10] = cosf(angle*TO_RAD);
        }
	void RotY(float angle)
        {
        mf[0]  =  cosf(angle*TO_RAD);
        mf[2]  =  -sinf(angle*TO_RAD);
        mf[8]  =  sinf(angle*TO_RAD);
        mf[10] =  cosf(angle*TO_RAD);    
        }
	void RotZ(float angle)
        {
        mf[0] =  cosf(angle*TO_RAD);
        mf[1] =  sinf(angle*TO_RAD);
        mf[4] =  -sinf(angle*TO_RAD);
        mf[5] =  cosf(angle*TO_RAD);
        }
};
