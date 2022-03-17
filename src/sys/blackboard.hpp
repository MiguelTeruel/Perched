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
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include "../util/typealiases.hpp"

template <typename GameCTX_t>
struct BlackBoardSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    //explicit CameraSystem() = default; //Constructor por defecto
    explicit BlackBoardSystem_t() = default;   //Constructor
                                                        //Destructor

    //            Este const implica que las variables con las que va a trabajar el metodo son conts del ambito de RenderSystem
    constexpr void update(GameCTX_t& g) const noexcept; //El GameContext no es const para que puedan modificarse los valores de las velocidades
};