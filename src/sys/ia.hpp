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
//# IASystem sirve para actualizar las entidades que tienen          #
//#   componente de ia, esto hace que actualicen sus comportamientos #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include <cstdint>
#include <stdio.h>
#include <iostream> 
#include <algorithm>
#include <cmath>
#include <iomanip>

#include "../cmp/ia.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/blackboard.hpp"


#include "../util/gameobjectfactory.hpp"
#include "../util/bt/behaviourtree.hpp"
#include "../util/typealiases.hpp"

template <typename GameCTX_t>
struct IASystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    //explicit IASystem() = default; //Constructor por defecto
    explicit IASystem_t(GameObjectFactory_t * gof) : my_gof{gof}{};   //Constructor
                                                        //Destructor

    //            Este const implica que las variables con las que va a trabajar el metodo son conts del ambito de RenderSystem
    bool update(GameCTX_t& g) const; //El GameContext no es const para que puedan modificarse los valores de las velocidades

    // bool arrive(IAComponent_t *, PhysicsComponent_t *) const;
    // bool seek(IAComponent_t *, PhysicsComponent_t *) const;

    private:
        GameObjectFactory_t * my_gof;
};