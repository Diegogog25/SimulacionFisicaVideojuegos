#include "Vector3D.h"


Vector3D::Vector3D() 
	: x(0.0f), y(0.0f), z(0.0f) {}

Vector3D::Vector3D(float _x, float _y, float _z) 
	: x(_x), y(_y), z(_z) {}

Vector3D::Vector3D(physx::PxVec3 v) 
	: x(v.x), y(v.y), z(v.z) {}

float 
Vector3D::magnitude() const 
{ 
	return sqrt(x * x + y * y + z * z); 
}

Vector3D
Vector3D::normalize() const {
	const float mag = magnitude();	
	return Vector3D( x / mag, y / mag , z / mag );
}

float
Vector3D::dot(const Vector3D& v) const{
	return x * v.x + y * v.y + z * v.z;
}

Vector3D
Vector3D::cross(const Vector3D& v) const{
	return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3D
Vector3D::operator+(const Vector3D& v) const
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D
Vector3D::operator-(const Vector3D& v) const 
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D
Vector3D::operator*(float f) const {
	return Vector3D(x * f, y * f, z * f);
}

Vector3D
Vector3D::operator=(const Vector3D& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3D
Vector3D::operator+=(const Vector3D& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
