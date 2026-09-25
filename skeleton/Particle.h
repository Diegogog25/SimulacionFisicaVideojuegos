#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
class Particle
{
public:
	//Sin Aceleracion
	Particle(Vector3D pos, Vector3D vel);
	//Con Aceleracion
	Particle(Vector3D pos, Vector3D vel, Vector3D acc);
	//Con damping
	Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damping);
	~Particle();

	void integrateEuler(double t) ;
	void semiImplicitEuler(double t);
	void integrateVerlet(double t);

private:
	Vector3D _vel;
	physx::PxTransform _pos;
	Vector3D _acc = Vector3D(0.0f, 0.0f, 0.0f);
	RenderItem* renderItem;
	float _d = 1.0f;
};

