#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	virtual ~ForceGenerator() = default;
	virtual void updateForce(Particle* p, double dt) = 0;
};