#pragma once

#include <vector>
#include <memory>

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleSystem.h"
#include "WindForceGenerator.h"
class P2_Scene : public Scene
{
public:
    explicit P2_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        //Suelo
        physx::PxShape* floorShape = CreateShape(physx::PxBoxGeometry(80.0f, 0.5f, 50.0f));
        _floorTransform = physx::PxTransform(physx::PxVec3(0.0f, FLOOR_TOP - 0.5f, 0.0f));
        _floor = new RenderItem(floorShape, &_floorTransform, Vector4(0.05f, 0.05f, 0.05f, 1.0f));
        //Chorro hacia arriba(rojo)
        auto g = std::make_unique<ParticleGenerator>(Vector3D{ 0.0f,0.0f,0.0f }, Vector3D{ 0.0f, 20.0f, 0.0f }, 8.0f, 1);
        g->setColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
        g->setRadius(0.5f);
        g->setPosSigma(Vector3D(0.2f, 0.0f, 0.2f));
        _system.addGenerator(std::move(g));

        //Niebla
        auto g2 = std::make_unique<ParticleGenerator>(Vector3D{ 40.0f, 5.0f, 0.0f }, Vector3D{ 0.0f, 0.5f, 0.0f }, 8.0f, 2);
        g2->setColor(Vector4(0.8f, 0.8f, 0.8f, 0.2f));
        g2->setRadius(0.15f);
        g2->setPosSigma(Vector3D(6.0f, 2.0f, 6.0f));
        g2->setVelSigma(Vector3D(0.5f, 0.3f, 0.5f));
        g2->setGravity(Vector3D(0.0f, 0.0f, 0.0f));
        _system.addGenerator(std::move(g2));

        // Fuego
        auto g3 = std::make_unique<ParticleGenerator>(Vector3D{ -30.0f, 0.0f, 0.0f }, Vector3D{ 0.0f, 6.0f, 0.0f }, 2.0f, 3);
        g3->setColor(Vector4(1.0f, 0.35f, 0.0f, 0.8f));
        g3->setRadius(0.25f);
        g3->setPosSigma(Vector3D(0.8f, 0.2f, 0.8f));
        g3->setVelSigma(Vector3D(0.8f, 1.5f, 0.8f));
        g3->setGravity(Vector3D(0.0f, 4.0f, 0.0f));
        g3->setUniform(true);
        _system.addGenerator(std::move(g3));

        _system.addForce(&_wind);
    }


    void update(double dt) override {
		_system.update(dt);
    }

    void cleanup() override {
		_system.clear();
        if (_floor) {
            _floor->release();
            _floor = nullptr;
        }
    }
private:
    static constexpr float FLOOR_TOP = -1.0f;
    WindForceGenerator _wind{ Vector3D(10.0f, 0.0f, 0.0f), 0.5f, Vector3D(0.0f, 10.0f, 0.0f), 50.0f };
	ParticleSystem _system;
    physx::PxTransform _floorTransform;
    RenderItem* _floor = nullptr;
};

