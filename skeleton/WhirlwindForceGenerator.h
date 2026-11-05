#pragma once
#include "WindForceGenerator.h"

class WhirlwindForceGenerator : public WindForceGenerator
{
public:
	WhirlwindForceGenerator(float K, float k1, const Vector3D& center, float radius)
		: WindForceGenerator(Vector3D(0, 0, 0), k1, center, radius), _K(K) {}

protected:
	//Gira alrededor del eje Y, centrado en _center
	Vector3D getWindVel(const Vector3D& pos) override {
		return Vector3D(-(pos.z - _center.z), 0.0f, pos.x - _center.x) * _K;
	}

private:
	//Fuerza
	float _K;	
};