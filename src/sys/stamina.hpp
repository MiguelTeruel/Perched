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
//# TextSystem sirve para actualizar las entidades que tienen        #
//#   componente de text, actualiza la parte variable del texto.     #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include "../cmp/stamina.hpp"

template <typename GameCTX_t>
struct StaminaSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    //explicit TextSystem() = default; //Constructor por defecto
    explicit StaminaSystem_t() = default;   //Constructor
                                                        //Destructor

    //            Este const implica que las variables con las que va a trabajar el metodo son conts del ambito de RenderSystem
    void update(GameCTX_t& g) const noexcept; //El GameContext no es const para que puedan modificarse los valores de las velocidades
    
};