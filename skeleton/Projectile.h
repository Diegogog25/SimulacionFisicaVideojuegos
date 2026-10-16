#pragma once
#include "Particle.h"
class Projectile : public Particle
{
public:
    Projectile(Vector3D pos, Vector3D dir, float massReal, 
        float velReal, float velSim, float radius, float damping, Vector4 color, bool floats = false);

    void setMassReal(float massReal);
    void setVelReal(float velReal);

    Vector3D getPosition() const { return Particle::getPosition(); }
    float getMassReal() const { return _massReal; }
    float getGravitySim() const { return _acc.y; }
	float getVelReal() const { return _velReal; }

private:
    void recompute();

    float _massReal;
    float _velReal;
    float _velSim;
    bool _floats;
	static constexpr float G_REAL = 9.81f;
};

