#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include <memory>
#include <vector>

class ForceGenerator;

class Particle
{
public:
	//Sin Aceleracion
	Particle(Vector3D pos, Vector3D vel);
	//Con Aceleracion
	Particle(Vector3D pos, Vector3D vel, Vector3D acc);
	//Con damping
	Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damping);
	Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damping, float mass, float radius, const Vector4& color);
	~Particle();

	void integrateEuler(double t) ;
	void semiImplicitEuler(double t);
	void integrateVerlet(double t);
	float getMass() const { return _mass; }
	bool isAlive() const { return _currLiveTime < _liveTime; }
	void setLifeTime(float lt) { _liveTime = lt; }
	Vector3D getPosition() const { return Vector3D(_pos.p); }

	//P3
	void addForce(const Vector3D& f) { _force += f; }
	void applyForces(const std::vector<ForceGenerator*>& forces, double dt);
	Vector3D getVelocity() const { return _vel; }
	//Para clonar una particula con las mismas propiedades
	std::unique_ptr<Particle> clone() const;
	//Setters
	void setPosition(const Vector3D& p) { _pos.p = p; }
	void setVelocity(const Vector3D& v) { _vel = v; }
	void hideRender() { if (renderItem) { renderItem->release(); renderItem = nullptr; } }
protected:

	Vector3D _vel;
	physx::PxTransform _pos;
	Vector3D _acc = Vector3D(0.0f, 0.0f, 0.0f);
	RenderItem* renderItem;
	float _d = 1.0f;
	float _mass = 1.0f;
	float _liveTime = 10.0f;
	float _currLiveTime = 0.0f;

	//P3
	Vector3D _force = Vector3D(0.0f, 0.0f, 0.0f);
	float _radius = 1.0f;
	Vector4 _color{ 1.0f, 1.0f, 0.0f, 1.0f };
};

