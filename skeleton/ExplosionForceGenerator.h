#pragma once
#include "ForceGenerator.h"
#include <cmath>

//Explosion: fuerza radial que se desvanece con el tiempo
class ExplosionForceGenerator : public ForceGenerator
{
public:
	ExplosionForceGenerator(const Vector3D& center, float K, float radius, float tau)
		: _center(center), _K(K), _radius(radius), _tau(tau) {
	}

	//Dispara la explosion(reinicia el tiempo)
	void explode() {
		_t = 0.0f;
		_active = true;
	}


	void update(double dt) {
		if (!_active) return;
		_t += dt;
		//A partir de 4 tau ya casi no queda fuerza, la desactivamos
		if (_t > 4.0f * _tau) _active = false;
	}

	void updateForce(Particle* p, double dt) override {
		if (!_active) return;

		Vector3D dir = p->getPosition() - _center;
		float r = dir.magnitude();
		//Fuera del radio no afecta
		if (r > _radius || r < 0.001f) return;

		//F = K / r^2 * (p - pc) * e^(-t/tau)
		float factor = (_K / (r * r)) * std::exp(-_t / _tau);
		p->addForce(dir * factor);
	}

private:
	Vector3D _center;
	//Intensidad de la explosion
	float _K;			
	float _radius;
	//COnstante de tiempo
	float _tau;			
	//Tiempo desde que explota
	float _t = 0.0f;	
	bool _active = false;
};