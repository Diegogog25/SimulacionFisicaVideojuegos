#pragma once
#include "ForceGenerator.h"

class WindForceGenerator : public ForceGenerator
{
public:
	WindForceGenerator(const Vector3D& windVel, float k1, const Vector3D& center, float radius)
		: _windVel(windVel), _k1(k1), _center(center), _radius(radius) {
	}

	void updateForce(Particle* p, double dt) override {
		//Si la particula esta fuera de la zona del viento no hace nada
		Vector3D dist = p->getPosition() - _center;
		if (dist.magnitude() > _radius) return;

		//Velocidad relativa entre el viento y la particula
		Vector3D relVel = getWindVel(p->getPosition()) - p->getVelocity();;

		//F = k1 * (velViento - velParticula)
		p->addForce(relVel * _k1);
	}

protected:
	//Para que los hijos puedan cambiarla
	virtual Vector3D getWindVel(const Vector3D& pos) { return _windVel; }

	Vector3D _windVel;
	//Coeficiente de rozamiento
	float _k1;			
	Vector3D _center;	
	float _radius;		
};