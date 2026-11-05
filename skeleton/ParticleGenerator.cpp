#include "ParticleGenerator.h"
ParticleGenerator::ParticleGenerator(Vector3D pos, Vector3D vel, float pLiveTime, int nParticles) :
	_pos(pos), _vel(vel), _pLiveTime(pLiveTime), _nParticles(nParticles) {

}
void
ParticleGenerator::update(double dt) {
	for (int i = 0; i < _nParticles; i++) {
		emit();
	}
	for (auto& p : _particles)
		p->semiImplicitEuler(dt);

	for (auto it = _particles.begin(); it != _particles.end();) {
		if (!(*it)->isAlive() || (*it)->getPosition().y < _minY)
			it = _particles.erase(it);
		else ++it;
	}

}

void
ParticleGenerator::emit() {
	Vector3D pos{ sample(_pos.x, _posSigma.x),
				  sample(_pos.y, _posSigma.y),
				  sample(_pos.z, _posSigma.z) };

	Vector3D vel{ sample(_vel.x, _velSigma.x),
				  sample(_vel.y, _velSigma.y),
				  sample(_vel.z, _velSigma.z) };

	auto p = std::make_unique<Particle>(pos, vel, _gravity, 0.9f, 1.0f, _radius, _color);
	p->setLifeTime(_pLiveTime);
	_particles.push_back(std::move(p));
}

float
ParticleGenerator::sample(float mid, float range) {
	if (range <= 0.0f) return mid;

	if (_uniform) {
		std::uniform_real_distribution<float> dist(mid - range, mid + range);
		return dist(_rng);
	}

	std::normal_distribution<float> dist(mid, range);
	return dist(_rng);
}