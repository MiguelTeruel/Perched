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
//# ColisionSystem sirve para actualizar las entidades que tienen    #
//#   componente de collider para saber si estan colisionando        #
//#   o no.                                                          #
//#                                                                  #
//####################################################################

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <functional>
#include <iostream>

#include "../util/typealiases.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/blackboard.hpp"
#include "../cmp/health.hpp"
#include "../cmp/control.hpp"
#include "../cmp/puntos.hpp"
#include "../cmp/follow.hpp"
#include "../cmp/stamina.hpp" 

template <typename GameCTX_t>
struct ColissionSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    explicit ColissionSystem_t(int32_t xmin, int32_t xmax, int32_t ymin, int32_t ymax);   //Constructor
                                                        //Destructor

    void sizeMapa(int32_t xmin, int32_t xmax, int32_t ymin, int32_t ymax) noexcept;

    bool update(GameCTX_t& g);

    void checkInteractuable(GameCTX_t& g);

    int checkAgujeros(GameCTX_t& g);

    void resetArbusto(GameCTX_t& g) noexcept;
    void resetCascada(GameCTX_t& g) noexcept;
    void addArbusto(GameCTX_t& g) noexcept;
    void addCascada(GameCTX_t& g) noexcept;

    bool getMeta(GameCTX_t& g) noexcept;
    void setMeta(GameCTX_t& g, bool llegar) noexcept;

    int getCrias(GameCTX_t& g) noexcept;
    void setCrias(GameCTX_t& g) noexcept;

    private:
        constexpr void borrarAlBorde(GameCTX_t& g, const ColliderComponent_t& inflicter) const noexcept;
        constexpr void checkMapColision(GameCTX_t& g, const ColliderComponent_t& col, PhysicsComponent_t& phy) const noexcept;
        BoundingBox_t<float> moveToWorldCoords(const BoundingBox_t<float>& box, float x, float y, float z) const noexcept;

        constexpr void checkBoundaryCollisions(const ColliderComponent_t& col, PhysicsComponent_t& phy) const noexcept;
        constexpr bool checkObjectCercaCollision(float dist, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2, const PhysicsComponent_t& phy1, const PhysicsComponent_t& phy2) const noexcept;

        constexpr bool checkPlayerSave(BoundingBoxNode_t& col1, BoundingBoxNode_t& col2, const PhysicsComponent_t& phy1, const PhysicsComponent_t& phy2) const noexcept;
        constexpr void checkIfPlayerSave(GameCTX_t& g) const noexcept;

        constexpr void react2collision(GameCTX_t& g, ColliderComponent_t& c1, ColliderComponent_t& c2, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) noexcept;
        constexpr void react2collision_ia(GameCTX_t& g, ColliderComponent_t& c1, ColliderComponent_t& c2, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) noexcept;
        
        constexpr void inflictDamage(GameCTX_t& g, ColliderComponent_t& other, ColliderComponent_t& player) const noexcept;
        constexpr void puntoControl(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept;
        constexpr void semilla(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept;
        constexpr void acelerar(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept;
        constexpr void decelerar(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept;
        constexpr void undoCollision(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) const noexcept;
        

        int32_t m_xmin { 0 }, m_xmax { 0 }, m_ymin { 0 }, m_ymax { 0 };

        int32_t arbusto { 0 };
        int32_t cascada { 0 };
        int32_t contArbusto { 0 };
        int32_t contCascada { 0 };

        bool llegaMeta { false };
        int criasRescatadas { 0 };
};
