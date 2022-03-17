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
//# CameraComponent sirve para guardar los datos necesarios que      #
//#   necesita la camara del juego para seguir a una entidad y       #
//#   tener un tamanyo de vision.                                    #
//#                                                                  #
//####################################################################

#pragma once
#include "component.hpp"
#include "../Motor3D/Node.hpp"

struct CameraComponent_t : public ECS::ComponentBase_t<CameraComponent_t> {
    explicit CameraComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    static constexpr uint32_t KdefaultWidth { 640 };
    static constexpr uint32_t KdefaultHeight { 360 };

    uint32_t srcx { 0 }, srcy { 0 };
    uint32_t w { 0 }, h { 0 };
    ECS::EntityID_t followEntityID { 0 };

    Node* camNode {};
};