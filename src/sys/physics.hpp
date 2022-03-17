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
//# PhysicsSystem sirve para actualizar las entidades que tienen     #
//#   componente de fisica, esto hace que actualicen las posiciones. #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>

#include "../util/typealiases.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/render.hpp"
#include "../cmp/ia.hpp"

#include "../util/path/pathP.hpp"


template <typename GameCTX_t>
struct PhysicsSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    //explicit PhysicsSystem() = default; //Constructor por defecto
    explicit PhysicsSystem_t() = default;   //Constructor
                                                        //Destructor

    void physicsRoca(GameCTX_t& g, PhysicsComponent_t& phy, ColliderComponent_t& col) const;
    void physicsIA(GameCTX_t& g, PhysicsComponent_t& phy) const;

    bool update(GameCTX_t& g); //El GameContext no es const para que puedan modificarse los valores de las velocidades
    void comprobarTunel(int quesubirbajar, GameCTX_t& g);
    bool entrarTunel(int quesubirbajar, GameCTX_t& g) const; 
    bool salirTunel(int quesubirbajar, GameCTX_t& g) const; 
    void calculozinicio(GameCTX_t& g); 
    void resetTunel(GameCTX_t& g) noexcept;
    void addTunel(GameCTX_t& g) noexcept;

    private:
        int cambioplano{0};
        int tunel{0};
        int contTunel{0};
};