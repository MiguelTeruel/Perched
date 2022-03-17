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
//# HealthSystem sirve para actualizar las entidades que tienen      #
//#   componente de health y destruir las que ya no tienen vida.     #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include "../util/typealiases.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/health.hpp"
#include "../cmp/render.hpp"
#include "../cmp/control.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/stamina.hpp"
#include "../Motor3D/Motor3D.hpp"

#include <iostream>

template <typename GameCTX_t>
struct HealthSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    //explicit HealthSystem() = default; //Constructor por defecto
    explicit HealthSystem_t() = default;   //Constructor
                                                        //Destructor

    //            Este const implica que las variables con las que va a trabajar el metodo son conts del ambito de RenderSystem
    constexpr void update(GameCTX_t& g, Motor3D* motor) const noexcept; //El GameContext no es const para que puedan modificarse los valores de las velocidades

    private:
        constexpr bool leafNodeCollided(const BoundingBoxNode_t& bn) const noexcept;
        constexpr void checkControl(GameCTX_t& g, HealthComponent_t& he, Motor3D* motor) const noexcept;
        constexpr void deleteNodes(GameCTX_t& g, const HealthComponent_t& he, Motor3D* motor) const noexcept;
};