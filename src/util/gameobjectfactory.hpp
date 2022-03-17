//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//# GameObjectFactory sirve para crear todos los objetos necesarios  #
//#   para crear el nivel.                                           #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include "../Motor3D/Motor3D.hpp"

#include "../picoJSON/picojson.hpp"
#include <string>
#include <string_view>
#include <wchar.h>
#include <fstream>
#include "../cmp/physics.hpp"
#include "../cmp/render.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/spawner.hpp"
#include "../cmp/health.hpp"
#include "../cmp/camera.hpp"
#include "../cmp/control.hpp"
#include "../cmp/text.hpp"
#include "../cmp/puntos.hpp"
#include "../cmp/follow.hpp"
#include "../cmp/stamina.hpp"
#include "../cmp/sound.hpp"
#include "../cmp/ia.hpp"
#include "../cmp/blackboard.hpp"

#include "../man/entitymanager.hpp"


//Forward declaration
namespace ECS {
    struct EntityManager_t;
    struct Entity_t;
}

struct GameObjectFactory_t {
    explicit GameObjectFactory_t(ECS::EntityManager_t& EntityMan, Motor3D* motor) : m_EntMan(EntityMan), motor(motor) {}

    ECS::Entity_t& createEntity(int32_t x, int32_t y, const std::string_view filename) const;
    ECS::Entity_t& createPlayer(const picojson::array &player) const;
    ECS::Entity_t& createCamera(int32_t x, int32_t y, uint32_t w, uint32_t h, ECS::EntityID_t followEID) const;
    ECS::Entity_t& createMeta(const picojson::array &meta) const;

    void createBT(BehaviourTree_t*) const ;
    ECS::Entity_t& createEnemy(const picojson::value &enemy, BehaviourTree_t *) const;
    void crearEnemigos (BehaviourTree_t*, const picojson::array &enemies) const;

    ECS::Entity_t& createRoca(int32_t x, int32_t y, int32_t vel, bool mover) const;
    void crearRocas (uint32_t cant) const;

    ECS::Entity_t& createSaliente(const picojson::value &saliente) const;
    void crearSalientes(const picojson::array &salientes) const;

    ECS::Entity_t& createNido(const picojson::value &nido) const;
    void crearNidos(const picojson::array &nidos, const picojson::array &crias) const;
    ECS::Entity_t& createCria(const picojson::value &cria, ECS::Entity_t& follow) const;

    ECS::Entity_t& createArbusto(const picojson::value &arbusto) const;
    void crearArbustos(const picojson::array &arbustos) const;

    ECS::Entity_t& createCascada(const picojson::value &cascada) const;
    void crearCascadas(const picojson::array &cascadas) const;

    ECS::Entity_t& createSemilla(const picojson::value &semilla) const;
    void crearSemillas(const picojson::array &semillas) const;

    ECS::Entity_t& createEnganche(const picojson::value &enganche) const;
    void crearEnganches(const picojson::array &enganches) const;

    ECS::Entity_t& createAgujero(const picojson::value &agujero) const;
    void crearAgujeros(const picojson::array &agujeros) const;

    ECS::Entity_t& createTelaranya(int32_t x, int32_t y, int32_t vel) const;

    ECS::Entity_t& createTrampolin(const picojson::value &trampolin) const;
    void crearTrampolines(const picojson::array &trampolines) const;

    void crearPlano(const picojson::array &plano) const;

    ECS::Entity_t& createMusgo(const picojson::value &musgo) const;
    void crearMusgos(const picojson::array &musgos) const;

    ECS::Entity_t& createHielo(const picojson::value &hielo) const;
    void crearHielos(const picojson::array &hielos) const;

    ECS::Entity_t& createPalo(int32_t x, int32_t y, int32_t vel, ECS::EntityID_t Entfollow) const;

    void unfollowPalo(ECS::EntityID_t Entounfollow) const;


    ECS::Entity_t& createPlanosEspeciales(const picojson::value &planoespecial) const;
    void crearPlanosEspeciales(const picojson::array &planosespeciales) const;

    void crearNavMesh(const picojson::array &plano) const;
    

    ECS::Entity_t& createText(std::string padre, std::vector<TextHijo_t> hijos, int32_t xmi, int32_t ymi, int32_t xma, int32_t yma) const;


    void loadLevelJSON(std::string_view filename, BehaviourTree_t*) const;
    //void JSONtoBIN(std::string_view jsonfile, std::string_view binfile) const;
    //void loadLevelBIN(std::string_view filename) const;

    //callback es la funcion a ejecutar cuando hace spawn
    template <typename CALL_t>
    ECS::Entity_t& createSpawner(uint32_t x, uint32_t y, CALL_t callback) const {
        auto& e = m_EntMan.createEntity();
        auto& sp = m_EntMan.addComponent<SpawnerComponent_t>(e);
        auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
        auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);

        //el spawner no debe colisionar, colisionan las entidades que crea
        
        ph.x = x;
        ph.y = y;
        ph.vy = 1;
        //ph.gravity = 0;

        sp.spawnMethod = callback;

        return e;
    }

    private:
        ECS::EntityManager_t& m_EntMan;
        Motor3D* motor;
};