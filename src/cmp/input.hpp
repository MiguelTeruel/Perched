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
//# InputComponent sirve para guardar los datos necesarios que       #
//#   necesita la entidad que tiene input para saber con que teclas  #
//#   hace el movimiento.                                            #
//#                                                                  #
//####################################################################

#pragma once

#include "../util/MyKeycodes.h"

#include <cstdint>
#include "component.hpp"
#include <X11/X.h>
#include <X11/keysym.h>

struct DistanciasCabeza_t {
    float disyCab { 0 }, disxCabDL { 0 }, disxCabDR { 0 }, disxCabU { 0 }, disxCabUL { 0 }, disxCabUR { 0 };
};

struct DistanciasPierna_t {
    float disx1 { 0 }, disx2 { 0 }, disy1 { 0 }, disy2 { 0 }, disy3 { 0 };
};

struct DistanciasBrazo_t {
    float disx1 { 0 }, disx2 { 0 }, disy1 { 0 }, disy2 { 0 }, disy3 { 0 }, disy4 { 0 };
};

struct InputComponent_t : public ECS::ComponentBase_t<InputComponent_t> {
    explicit InputComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    keys::KEY_CODE key_LEFT { keys::KEY_CODE::KEY_KEY_A };
    keys::KEY_CODE key_RIGHT { keys::KEY_CODE::KEY_KEY_D };
    keys::KEY_CODE key_UP { keys::KEY_CODE::KEY_KEY_W };
    keys::KEY_CODE key_DOWN { keys::KEY_CODE::KEY_KEY_S };

    DistanciasCabeza_t distsCabeza {};
    DistanciasPierna_t distsPiernaI {};
    DistanciasPierna_t distsPiernaD {};
    DistanciasBrazo_t distsBrazoI {};
    DistanciasBrazo_t distsBrazoD {};
};