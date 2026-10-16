#include "Projectile.h"
Projectile::Projectile(Vector3D pos, Vector3D dir, float massReal, float velReal, float velSim, float radius, float damping, Vector4 color, bool floats)
    : Particle(pos, dir.normalize()* velSim, Vector3D(0.0f, 0.0f, 0.0f),
		damping, massReal, radius, color), _massReal(massReal), _velReal(velReal), _velSim(velSim), _floats(floats)
{
    recompute();
}

void Projectile::setMassReal(float massReal)
{
    _massReal = massReal;
    recompute();
}

void Projectile::setVelReal(float velReal)
{
    _velReal = velReal;
    recompute();
}

void Projectile::recompute()
{
    const float ratio = _velReal / _velSim;

    _mass = _massReal * ratio * ratio;

    const float gSim = G_REAL / (ratio * ratio);
    _acc = Vector3D(0.0f,_floats ? gSim : -gSim, 0.0f);
}