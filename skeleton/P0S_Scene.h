#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
class P0S_Scene : public Scene
{
public:
    explicit P0S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

        Vector3D axe_X(3.0f, 1.0f, 0.0f);
        Vector3D axe_Y(0.0f, 4.0f, 0.0f);
        Vector3D axe_Z = axe_X.cross(axe_Y);

        axe_X = axe_X.normalize() * 5.0f;
        axe_Y = axe_Y.normalize() * 5.0f;
        axe_Z = axe_Z.normalize() * 5.0f;

        m_transforms.reserve(4);

        m_transforms.emplace_back(physx::PxVec3(0.0f, 0.0f, 0.0f));
        m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(1.0f, 1.0f, 0.0f, 1.0f)));

        //m_transforms.emplace_back(physx::PxVec3(axe_X.x, axe_X.y, axe_X.z));
        //m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

        //m_transforms.emplace_back(physx::PxVec3(axe_Y.x, axe_Y.y, axe_Y.z));
        //m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(0.0f, 1.0f, 0.0f, 1.0f)));

        //m_transforms.emplace_back(physx::PxVec3(axe_Z.x, axe_Z.y, axe_Z.z));
        //m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(0.0f, 0.0f, 1.0f, 1.0f)));

        m_transforms.emplace_back(physx::PxVec3(2.0f, 0.0f, 3.0f));
        m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

        m_transforms.emplace_back(physx::PxVec3(-4.0f, 0.0f, 1.0f));
        m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(0.0f, 1.0f, 0.0f, 1.0f)));

        m_transforms.emplace_back(physx::PxVec3(0.0f, 0.0f, 5.0f));
        m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(0.0f, 0.0f, 1.0f, 1.0f)));

        m_transforms.emplace_back(physx::PxVec3(0.0f, 0.0f, 0.0f));
        m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(0.0f, 0.0f, 1.0f, 1.0f)));



    }


    void update(double dt) override {}

    void cleanup() override {
		for (auto* item : m_renderItems) {
			if(item) {
				item->release();
			}
		}
		m_renderItems.clear();
		m_transforms.clear();   
    }
private:

    std::vector<physx::PxTransform> m_transforms;
    std::vector<RenderItem*> m_renderItems;

};

