#pragma once
#include <vector>
#include <memory>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"


class ParticleSystem
{
public:
	//Para poder desactivar/activar
	size_t addGenerator(std::unique_ptr<ParticleGenerator> g);

	void setGeneratorActive(size_t i, bool active);
	void toggleGenerator(size_t i);

	void update(double dt);
	void clear();
	void setMinY(float y) { _minY = y; }

	void addForce(ForceGenerator* f);
	void removeForce(ForceGenerator* f);
	void changeForce(ForceGenerator* f);
	bool hasForce(ForceGenerator* f) const;

private:
	struct GenEntry { std::unique_ptr<ParticleGenerator> gen; bool active; };

	std::vector<GenEntry> _gens;
	std::vector<std::unique_ptr<Particle>> _particles;
	float _minY = -10.0f;

	std::vector<ForceGenerator*> _forces;

};