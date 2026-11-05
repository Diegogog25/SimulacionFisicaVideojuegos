#pragma once

#include <vector>
#include <memory>
#include <cctype>

#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"

class P3_Scene : public Scene
{
public:
    explicit P3_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        //Suelo
        physx::PxShape* floorShape = CreateShape(physx::PxBoxGeometry(80.0f, 0.5f, 50.0f));
        _floorTransform = physx::PxTransform(physx::PxVec3(0.0f, FLOOR_TOP - 0.5f, 0.0f));
        _floor = new RenderItem(floorShape, &_floorTransform, Vector4(0.05f, 0.05f, 0.05f, 1.0f));

        Vector3D sinAcc(0, 0, 0);
        Vector3D vUp(0, 10, 0);

        //Gravedad misma gravedad y distinta masa, caen igual
        crearEmisor(_sysN, Vector3D(-30, 0, -20), vUp, Vector4(1, 0, 0, 1), 1.0f, sinAcc);
        crearEmisor(_sysP, Vector3D(-22, 0, -20), vUp, Vector4(1, 0.5f, 0, 1), 10.0f, sinAcc);
        _sysN.addForce(&_gravNormal);
        _sysP.addForce(&_gravNormal);

        //Gravedad ligera, sube mas y cae mas despacio
        crearEmisor(_sysL, Vector3D(-14, 0, -20), vUp, Vector4(0, 1, 0, 1), 1.0f, sinAcc);
        _sysL.addForce(&_gravLigera);

        //Para comparar esta tiene gravedad como acelaracion
        crearEmisor(_sysC, Vector3D(-6, 0, -20), vUp, Vector4(0, 0, 1, 1), 1.0f, Vector3D(0, -9.8f, 0));

        //Viento en una particula ligera y otra pesada
        crearEmisor(_sysVientoL, Vector3D(10, 0, 8), vUp, Vector4(1, 0, 0, 1), 1.0f, sinAcc);
        crearEmisor(_sysVientoP, Vector3D(10, 0, 14), vUp, Vector4(1, 0.5f, 0, 1), 10.0f, sinAcc);
        _sysVientoL.addForce(&_gravNormal);
        _sysVientoL.addForce(&_wind);
        _sysVientoP.addForce(&_gravNormal);
        _sysVientoP.addForce(&_wind);

        //Torbellino
        crearEmisor(_sysTorbellino, Vector3D(-20, 10, 20), Vector3D(0, 0, 0), Vector4(0.6f, 0.2f, 1, 1), 1.0f, sinAcc, Vector3D(5, 1, 5));
        _sysTorbellino.addForce(&_whirl);

        //Explosion, masa 1 y masa 8
        crearEmisor(_sysExplosion, Vector3D(25, 5, -20), Vector3D(0, 0, 0), Vector4(1, 1, 0, 1), 1.0f, sinAcc, Vector3D(6, 1, 6));
        crearEmisor(_sysExplosion, Vector3D(25, 5, -20), Vector3D(0, 0, 0), Vector4(1, 0.5f, 0, 1), 8.0f, sinAcc, Vector3D(6, 1, 6));
        _sysExplosion.addForce(&_explosion);

        _todos = { &_sysN, &_sysP, &_sysL, &_sysC, &_sysVientoL, &_sysVientoP, &_sysTorbellino, &_sysExplosion };

        //Las particulas desaparecen al llegar al suelo
        for (auto* s : _todos) s->setMinY(FLOOR_TOP);
    }

    void update(double dt) override {
        _explosion.update(dt);
        for (auto* s : _todos) s->update(dt);
    }

    void cleanup() override {
        for (auto* s : _todos) s->clear();
        if (_floor) {
            _floor->release();
            _floor = nullptr;
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& cam) override {
        switch (std::toupper(key)) {
        case 'T':   //Viento
            _sysVientoL.changeForce(&_wind);
            _sysVientoP.changeForce(&_wind);
            break;
        case 'Y':   //Torbellino
            _sysTorbellino.changeForce(&_whirl);
            break;
        case 'X':   //Explosion
            _explosion.explode();
            break;
        }
    }

private:
    //Crea un emisor y se lo da al sistema, el radio depende de la masa para distinguirlas
    void crearEmisor(ParticleSystem& sys, Vector3D pos, Vector3D vel, Vector4 color, float masa,
        Vector3D acc, Vector3D posSigma = Vector3D(0, 0, 0)) {
        auto g = std::make_unique<ParticleGenerator>(pos, vel, 8.0f, 1);
        g->setColor(color);
        g->setRadius(0.3f + 0.05f * masa);
        g->setMass(masa);
        g->setPosSigma(posSigma);
        g->setVelSigma(Vector3D(0, 0, 0));
        g->setGravity(acc);
        sys.addGenerator(std::move(g));
    }

    static constexpr float FLOOR_TOP = -1.0f;

	//Sistemas de particulas
    ParticleSystem _sysN, _sysP, _sysL, _sysC;
    ParticleSystem _sysVientoL, _sysVientoP;
    ParticleSystem _sysTorbellino;
    ParticleSystem _sysExplosion;
    std::vector<ParticleSystem*> _todos;

    //Generadores de fuerza
    GravityForceGenerator _gravNormal{ Vector3D(0.0f, -9.8f, 0.0f) };
    GravityForceGenerator _gravLigera{ Vector3D(0.0f, -2.0f, 0.0f) };
    WindForceGenerator _wind{ Vector3D(10.0f, 0.0f, 0.0f), 0.5f, Vector3D(20.0f, 8.0f, 11.0f), 25.0f };
    WhirlwindForceGenerator _whirl{ 1.0f, 0.5f, Vector3D(-20.0f, 10.0f, 20.0f), 30.0f };
    ExplosionForceGenerator _explosion{ Vector3D(25.0f, 5.0f, -20.0f), 100.0f, 25.0f, 1.0f };

    physx::PxTransform _floorTransform;
    RenderItem* _floor = nullptr;
};