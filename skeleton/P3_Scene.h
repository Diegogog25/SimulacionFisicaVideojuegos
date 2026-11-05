#pragma once

#include <vector>
#include <memory>

#include "Scene.h"
#include "Particle.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"

class P3_Scene : public Scene
{
public:
    explicit P3_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        _gravNormal = std::make_unique<GravityForceGenerator>(Vector3D(0.0f, -9.8f, 0.0f));
        _gravLigera = std::make_unique<GravityForceGenerator>(Vector3D(0.0f, -2.0f, 0.0f));

        crearParticula(Vector3D(-10, 20, 0), 1.0f, Vector4(1, 0, 0, 1), _gravNormal.get());
        crearParticula(Vector3D(-5, 20, 0), 5.0f, Vector4(1, 0.5f, 0, 1), _gravNormal.get());
        crearParticula(Vector3D(0, 20, 0), 1.0f, Vector4(0, 1, 0, 1), _gravLigera.get());

		//Para comparar(a esta no se le aplca fuerza, solo gravedad)
        auto control = std::make_unique<Particle>(Vector3D(5, 20, 0), Vector3D(0, 0, 0), Vector3D(0.0f, -9.8f, 0.0f), 1.0f, 1.0f, 0.5f, Vector4(0, 0, 1, 1));
        control->setLifeTime(1000.0f);
        _particles.push_back(std::move(control));
    }

    void update(double dt) override {
        _registry.updateForces(dt);
        for (auto& p : _particles)
            p->semiImplicitEuler(dt);
    }

    void cleanup() override {
        _registry.clear();
        _particles.clear();
    }

private:
    void crearParticula(Vector3D pos, float masa, Vector4 color, ForceGenerator* gen) {
        auto p = std::make_unique<Particle>(pos, Vector3D(0, 0, 0), Vector3D(0, 0, 0), 1.0f, masa, 0.5f, color);
        p->setLifeTime(1000.0f);
        _registry.add(p.get(), gen);
        _particles.push_back(std::move(p));
    }

    ForceRegistry _registry;
    std::vector<std::unique_ptr<Particle>> _particles;
    std::unique_ptr<GravityForceGenerator> _gravNormal;
    std::unique_ptr<GravityForceGenerator> _gravLigera;
};