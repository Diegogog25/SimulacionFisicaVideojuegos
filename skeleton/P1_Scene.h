#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"
class P1_Scene : public Scene
{
public:
    explicit P1_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {

 
    }


    void update(double dt) override {
        //particle_vel->integrate(0.1);
		//particle_acc->integrate(0.1);
		particle_damp->integrateEuler(dt);
    }

    void cleanup() override {
        for (auto* item : m_renderItems) {
            if (item) {
                item->release();
            }
        }
        m_renderItems.clear();
        m_transforms.clear();
    }
private:

    std::vector<physx::PxTransform> m_transforms;
    std::vector<RenderItem*> m_renderItems;

    //Sin aceleracion
    //Particle* particle_vel = new Particle(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(1.0f, 0.0f, 0.0f));
	//Con aceleracion
	//Particle* particle_acc = new Particle(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.1f, 0.0f));

	//Con damping
	Particle* particle_damp = new Particle(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.1f, 0.0f), 1.0f);

};

