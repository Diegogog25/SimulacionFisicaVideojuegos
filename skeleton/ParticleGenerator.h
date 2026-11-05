#pragma once
#include "Particle.h"
#include "Vector3D.h"
#include <iostream>
#include <vector>
#include <memory>
#include <random>
class ParticleGenerator
{
public:
	ParticleGenerator(Vector3D pos, Vector3D vel, float pLiveTime, int nParticles);
	void update(double dt);

	//Setters(Para poder cambiar desde la escena)
	void setColor(const Vector4& c) { _color = c; }
	void setRadius(float r) { _radius = r; }
	void setPosSigma(const Vector3D& s) { _posSigma = s; }
	void setVelSigma(const Vector3D& s) { _velSigma = s; }
	void setGravity(const Vector3D& g) { _gravity = g; }
	void setUniform(bool u) { _uniform = u; }

	//Si queremos cambiar el limite en el que se eliminan las particulas
	void setMinY(float y) { _minY = y; }
private:

	void emit();

	float sample(float mean, float stddev);

	//Si es true, usa la distribucion uniforme, sino la normal
	bool _uniform = false;

	std::vector<std::unique_ptr<Particle>> _particles;

	Vector3D _pos{ 0.0f, 0.0f, 0.0f };
	Vector3D _vel{ 1.0f, 2.0f, 0.0f };
	Vector3D _gravity{ 0.0f, -10.0f, 0.0f };
	Vector4 _color{ 0.2f, 0.5f, 1.0f, 1.0f };
	float _radius = 0.3f;

	float _pLiveTime = 8.0f;
	int _nParticles = 4;
	// si sobrepasa el limite se eliminan
	float _minY = -10.0f;
	std::mt19937 _rng{ std::random_device{}() };

	Vector3D _velSigma{ 2.0f, 2.0f, 2.0f };
	Vector3D _posSigma{ 2.0f, 2.0f, 2.0f };
};

