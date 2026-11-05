#pragma once
#include <vector>
#include <algorithm>
#include "ForceGenerator.h"

class ForceRegistry
{
public:
	void add(Particle* p, ForceGenerator* g) { _regs.push_back({ p, g }); }

	void removeParticle(Particle* p) {
		_regs.erase(std::remove_if(_regs.begin(), _regs.end(), [p](const Reg& r) { return r.p == p; }), _regs.end());
	}

	void clear() { _regs.clear(); }

	void updateForces(double dt) {
		for (auto& r : _regs) r.g->updateForce(r.p, dt);
	}

private:
	//Para saber que gen tiene cada particula
	struct Reg { Particle* p; ForceGenerator* g; };
	std::vector<Reg> _regs;
};