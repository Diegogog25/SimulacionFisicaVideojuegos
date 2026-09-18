#pragma once
#include <foundation/PxSimpleTypes.h>
#include <PxPhysicsVersion.h>
#include "foundation/PxMath.h"
#include <cmath>
#include "PxPhysicsAPI.h"
#include <vector>
class Vector3D
{
public:

	Vector3D();
	Vector3D(float _x, float _y, float _z) ;
	Vector3D(physx::PxVec3 v) ;
	float magnitude() const;
	Vector3D normalize() const;
	float dot(const Vector3D& v) const;
	Vector3D cross(const Vector3D& v) const;


	float x, y, z;
};

