#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleGenerator.h"
class P1_Scene : public Scene
{
public:
    explicit P1_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
       _gen = std::make_unique<ParticleGenerator>(Vector3D{0.0f,0.0f,0.0f},Vector3D{0.0f, 20.0f, 0.0f}, 8.0f, 1.0f);
 
    }


    void update(double dt) override {
        _gen->update(dt);
    }

    void cleanup() override {
        _gen.reset();
    }
private:
    std::unique_ptr<ParticleGenerator> _gen;

};

