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

	//Setters(Para poder cambiar desde la escena)
	void setPosSigma(const Vector3D& s) { _posSigma = s; }
	void setVelSigma(const Vector3D& s) { _velSigma = s; }
	void setColor(const Vector4& c) { _color = c; rebuildModel(); }
	void setRadius(float r) { _radius = r; rebuildModel(); }
	void setGravity(const Vector3D& g) { _gravity = g; rebuildModel(); }
	void setUniform(bool u) { _uniform = u; }
	void setMass(float m) { _mass = m; rebuildModel(); }

	//P3
	void generate(std::vector<std::unique_ptr<Particle>>& out);
private:

	std::unique_ptr<Particle> emit();

	float sample(float mean, float stddev);

	//Si es true, usa la distribucion uniforme, sino la normal
	bool _uniform = false;


	Vector3D _pos{ 0.0f, 0.0f, 0.0f };
	Vector3D _vel{ 1.0f, 2.0f, 0.0f };
	Vector3D _gravity{ 0.0f, -10.0f, 0.0f };
	Vector4 _color{ 0.2f, 0.5f, 1.0f, 1.0f };
	float _radius = 0.3f;

	float _pLiveTime = 8.0f;
	int _nParticles = 4;

	std::mt19937 _rng{ std::random_device{}() };

	Vector3D _velSigma{ 2.0f, 2.0f, 2.0f };
	Vector3D _posSigma{ 2.0f, 2.0f, 2.0f };

	//P3
	std::unique_ptr<Particle> _model;
	void rebuildModel();
	float _mass = 1.0f;
};

