#pragma once
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator
{
public:
	explicit GravityForceGenerator(const Vector3D& g) : _g(g) {}

	void updateForce(Particle* p, double dt) override {
		//F = m * g
		p->addForce(_g * p->getMass());
	}

	void setGravity(const Vector3D& g) { _g = g; }

private:
	Vector3D _g;
};