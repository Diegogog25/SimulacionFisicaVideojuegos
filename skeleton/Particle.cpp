#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel)
	: _vel(vel), _pos(pos.x, pos.y, pos.z), _acc(0.0f, 0.0f, 0.0f)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(shape, &_pos, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
}


Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc)
	: _vel(vel), _pos(pos.x, pos.y, pos.z), _acc(acc)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(shape, &_pos, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
}

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damping)
	: _vel(vel), _pos(pos.x, pos.y, pos.z), _acc(acc), _d(damping)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(shape, &_pos, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
}

Particle::~Particle()
{
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void
Particle::integrateEuler(double t)
{
	_pos.p += _vel * t;
	_vel = _vel * pow(_d, t) + _acc * t;
}

void
Particle::semiImplicitEuler(double t)
{
	_vel = _vel * pow(_d, t) + _acc * t;
	_pos.p += _vel * t;
}

void
Particle::integrateVerlet(double t) {

}