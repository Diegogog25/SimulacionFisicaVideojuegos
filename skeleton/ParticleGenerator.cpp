#include "ParticleGenerator.h"
ParticleGenerator::ParticleGenerator(Vector3D pos, Vector3D vel, float pLiveTime, int nParticles) :
	_pos(pos), _vel(vel), _pLiveTime(pLiveTime), _nParticles(nParticles) {

}
void
ParticleGenerator::update(double dt) {
	for (int i = 0; i < _nParticles; i++) emitPos();
	for (auto& p : _particles)
		p->semiImplicitEuler(dt);

	for (auto it = _particles.begin(); it != _particles.end();) {
		if (!(*it)->isAlive() || (*it)->getPosition().y < _minY)
			it = _particles.erase(it);
		else ++it;
	}

}

void ParticleGenerator::emitVel() {
	std::normal_distribution<float> distX(_vel.x, _velSigma.x);
	std::normal_distribution<float> distY(_vel.x, _velSigma.x);
	std::normal_distribution<float> distZ(_vel.x, _velSigma.x);
	float vx = distX(_rng);
	float vy = distY(_rng);
	float vz = distZ(_rng);
	Vector3D v{ vx, vy, vz };
	auto p = std::make_unique<Particle>(_pos, v, _gravity, 0.9f, 1.0f, 0.3f, Vector4(0.2f, 0.5f, 1.0f, 1.0f));
	p->setLifeTime(_pLiveTime);
	_particles.push_back(std::move(p));
}

void ParticleGenerator::emitPos() {
	std::normal_distribution<float> posX(_pos.x, _posSigma.x);
	std::normal_distribution<float> posY(_pos.y, _posSigma.y);
	std::normal_distribution<float> posZ(_pos.z, _posSigma.z);
	float px = posX(_rng);
	float py = posY(_rng);
	float pz = posZ(_rng);
	Vector3D pos{ px, py, pz };
	auto p = std::make_unique<Particle>(pos, _vel, _gravity, 0.9f, 1.0f, 0.3f, Vector4(0.2f, 0.5f, 1.0f, 1.0f));
	p->setLifeTime(_pLiveTime);
	_particles.push_back(std::move(p));
}