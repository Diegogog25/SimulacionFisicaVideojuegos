#include "ParticleSystem.h"
#include <algorithm>

size_t
ParticleSystem::addGenerator(std::unique_ptr<ParticleGenerator> g) {
	_gens.push_back({ std::move(g), true });
	return _gens.size() - 1;
}

void
ParticleSystem::setGeneratorActive(size_t i, bool active) {
	if (i < _gens.size()) _gens[i].active = active;
}

void
ParticleSystem::toggleGenerator(size_t i) {
	if (i < _gens.size()) _gens[i].active = !_gens[i].active;
}

void
ParticleSystem::update(double dt) {
	// Los activos crean particulas nuevas
	for (auto& g : _gens)
		if (g.active) g.gen->generate(_particles);
	
	for (auto& p : _particles)
		p->applyForces(_forces, dt);

	for (auto& p : _particles)
		p->semiImplicitEuler(dt);

	// Eliminamos las que no estan vivas
	for (auto it = _particles.begin(); it != _particles.end();) {
		if (!(*it)->isAlive() || (*it)->getPosition().y < _minY)
			it = _particles.erase(it);
		else ++it;
	}
}

void
ParticleSystem::clear() {
	_particles.clear();
}

void
ParticleSystem::addForce(ForceGenerator* f) {
	if (!hasForce(f)) _forces.push_back(f);
}

void
ParticleSystem::removeForce(ForceGenerator* f) {
	_forces.erase(std::remove(_forces.begin(), _forces.end(), f), _forces.end());
}

void
ParticleSystem::changeForce(ForceGenerator* f) {
	if (hasForce(f)) removeForce(f);
	else addForce(f);
}

bool
ParticleSystem::hasForce(ForceGenerator* f) const {
	return std::find(_forces.begin(), _forces.end(), f) != _forces.end();
}