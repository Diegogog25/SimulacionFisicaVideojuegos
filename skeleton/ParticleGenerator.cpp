#include "ParticleGenerator.h"
ParticleGenerator::ParticleGenerator(Vector3D pos, Vector3D vel, float pLiveTime, int nParticles) :
	_pos(pos), _vel(vel), _pLiveTime(pLiveTime), _nParticles(nParticles) {

}

void
ParticleGenerator::generate(std::vector<std::unique_ptr<Particle>>& out) {
	for (int i = 0; i < _nParticles; i++)
		out.push_back(emit());
}

void
ParticleGenerator::rebuildModel() {
	_model = std::make_unique<Particle>(_pos, _vel, _gravity, 0.9f, _mass, _radius, _color);
	_model->setLifeTime(_pLiveTime);
	//Para que no se vea la particula modelo
	_model->hideRender();
}

std::unique_ptr<Particle>
ParticleGenerator::emit() {
	Vector3D pos{ sample(_pos.x, _posSigma.x),
				  sample(_pos.y, _posSigma.y),
				  sample(_pos.z, _posSigma.z) };

	Vector3D vel{ sample(_vel.x, _velSigma.x),
				  sample(_vel.y, _velSigma.y),
				  sample(_vel.z, _velSigma.z) };

	auto p = _model->clone();
	p->setPosition(pos);
	p->setVelocity(vel);
	return p;
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