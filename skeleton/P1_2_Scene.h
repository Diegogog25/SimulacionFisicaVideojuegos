#pragma once
#include "Scene.h"
#include "Projectile.h"
#include <vector>
#include <memory>
#include <cctype>
class P1_2_Scene : public Scene
{
public:
    explicit P1_2_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {}

    void keyPress(unsigned char key, const physx::PxTransform& cam) override {
        switch (std::toupper(key)) {
        case 'B': shootBall(cam); break;
		case 'C': shootBullet(cam); break;
        case 'R': increaseProjectileSpeed(); break;
        }
    }

    void update(double dt) override {
        for (auto& s : m_shots) {
            s.p->semiImplicitEuler(dt);
            s.age += dt;
        }
        for (auto it = m_shots.begin(); it != m_shots.end();) {
            if (it->age > 15.0 || it->p->getPosition().y < -100.0f)
                it = m_shots.erase(it);
            else ++it;
        }
    }

    void cleanup() override { m_shots.clear(); }

private:
    struct Shot { std::unique_ptr<Projectile> p; double age = 0.0; };

    void increaseProjectileSpeed() {
        m_increasedVelReal *= 1.1f;
        for (auto& shot : m_shots) {
            shot.p->setVelReal(shot.p->getVelReal() * 1.1f);
        }
    }

    void shootBall(const physx::PxTransform& cam) {
        physx::PxVec3 dir = cam.q.rotate(physx::PxVec3(0, 0, -1));
        m_shots.push_back({ std::make_unique<Projectile>(
            Vector3D(cam.p), Vector3D(dir),
            m_ballMassReal, 8.0f * m_increasedVelReal, 4.0f, 0.12f, 0.98f, Vector4(1.0f, 0.5f, 0.0f, 1.0f), false), 0.0 });
    }

    void shootBullet(const physx::PxTransform& cam) {
		physx::PxVec3 dir = cam.q.rotate(physx::PxVec3(0, 0, -1));
        m_shots.push_back({ std::make_unique<Projectile>(
            Vector3D(cam.p), Vector3D(dir),
            m_bulletMassReal, 360.0f * m_increasedVelReal, 24.0f, 0.035f, 0.995f, Vector4(0.65f, 0.65f, 0.68f, 1.0f), false), 0.0 });
    }

    float m_ballMassReal = 0.62f;
	float m_bulletMassReal = 0.008f;
    float m_increasedVelReal = 1.0f;
    std::vector<Shot> m_shots;
};

