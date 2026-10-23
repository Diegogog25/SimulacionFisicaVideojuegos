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
private:

	void emitVel();
	void emitPos();

	std::vector<std::unique_ptr<Particle>> _particles;
	Vector3D _pos{ 0.0f, 0.0f, 0.0f };
	Vector3D _vel{ 1.0f, 2.0f, 0.0f };
	Vector3D _gravity{ 0.0f, -10.0f, 0.0f };
	float _pLiveTime = 8.0f;
	int _nParticles = 4;
	// si sobrepasa el limite se eliminan
	float _minY = -10.0f;
	std::mt19937 _rng;
	Vector3D _velSigma{ 2.0f, 2.0f, 2.0f };

	Vector3D _posSigma{ 2.0f, 2.0f, 2.0f };
	Vector4 _colorSigma{ 1.0f, 1.0f, 0.0f, 1.0f };
};

