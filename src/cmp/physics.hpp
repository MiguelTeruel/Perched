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
//# PhysicsComponent sirve para guardar los datos necesarios que     #
//#   necesita una entidad para conocer su posicion, su rotacion,    #
//#   su velocidad y su ultima posicion.                             #
//#                                                                  #
//####################################################################

#pragma once
#include <cstdint>
#include "component.hpp"

#define PI 3.141592 

struct PhysicsComponent_t : public ECS::ComponentBase_t<PhysicsComponent_t> {
    explicit PhysicsComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    //const es solo lectura
    static constexpr float Kgravity { 0.05f };
    static constexpr float KminVy { -6.0f };
    static constexpr float KmaxVy { 6.0f };
    static constexpr float KminVx { -5.0f };
    static constexpr float KmaxVx { 5.0f };
    
    float x { 0 }, y { 0 }, z { 0 };
    float last_x{ 0 }, last_y { 0 }, last_z { 0 };
    float vx { 0 }, vy { 0 }, vz { 0 };
    int32_t rotx { 0 }, roty { 0 }, rotz { 0 };
    double orientation { 0.0 };
    float zinicial { 0 };

    bool pasomusgo { false };
    bool pasohielo { false };

    float friction { 1.0f }; 
    float gravity { Kgravity };

    double v_linear  { 0.0 };
    double v_angular { 0.0 };

    static constexpr double KmaxVLin {0.65};
    static constexpr double KmaxVang {PI/10};
    double Kepsilon {10};
};