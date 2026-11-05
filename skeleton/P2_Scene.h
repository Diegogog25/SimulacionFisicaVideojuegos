#pragma once

#include <vector>
#include <memory>

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleGenerator.h"
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
        _gens.push_back(std::make_unique<ParticleGenerator>(Vector3D{ 0.0f,0.0f,0.0f }, Vector3D{ 0.0f, 20.0f, 0.0f }, 8.0f, 1));

		_gens.back()->setColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		_gens.back()->setRadius(0.5f);
		_gens.back()->setPosSigma(Vector3D(0.2f, 0.0f, 0.2f));

        //Niebla
        _gens.push_back(std::make_unique<ParticleGenerator>(Vector3D{ 40.0f, 5.0f, 0.0f }, Vector3D{ 0.0f, 0.5f, 0.0f }, 8.0f, 2));
        _gens.back()->setColor(Vector4(0.8f, 0.8f, 0.8f, 0.2f));
        _gens.back()->setRadius(0.15f);
        _gens.back()->setPosSigma(Vector3D(6.0f, 2.0f, 6.0f));
        _gens.back()->setVelSigma(Vector3D(0.5f, 0.3f, 0.5f));
        _gens.back()->setGravity(Vector3D(0.0f, 0.0f, 0.0f));

        // Fuego
        _gens.push_back(std::make_unique<ParticleGenerator>(Vector3D{ -30.0f, 0.0f, 0.0f }, Vector3D{ 0.0f, 6.0f, 0.0f }, 2.0f, 3));
        _gens.back()->setColor(Vector4(1.0f, 0.35f, 0.0f, 0.8f));
        _gens.back()->setRadius(0.25f);
        _gens.back()->setPosSigma(Vector3D(0.8f, 0.2f, 0.8f));
        _gens.back()->setVelSigma(Vector3D(0.8f, 1.5f, 0.8f));
        _gens.back()->setGravity(Vector3D(0.0f, 4.0f, 0.0f));
        _gens.back()->setUniform(true);
    }


    void update(double dt) override {
        for (auto& gen : _gens) {
            gen->update(dt);
        }
    }

    void cleanup() override {
        _gens.clear();
        if (_floor) {
            _floor->release();
            _floor = nullptr;
        }
    }
private:
    static constexpr float FLOOR_TOP = -1.0f;

    std::vector<std::unique_ptr<ParticleGenerator>> _gens;
    physx::PxTransform _floorTransform;
    RenderItem* _floor = nullptr;
};

