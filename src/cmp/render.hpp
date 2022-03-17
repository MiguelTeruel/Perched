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
//# RenderComponent sirve para guardar los datos necesarios que      #
//#   necesita una entidad para saber sus dimensiones y tener        #
//#   nodos asociados.                                               #
//#                                                                  #
//####################################################################

#pragma once

#include "../Motor3D/Node.hpp"

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <string_view>
#include "component.hpp"

struct ChildNode_t {
    Node* node;
    float x { 0 }, y { 0 }, z { 0 };
    std::string parte;
    float disx { 0 }, disy { 0 }, disz { 0 };
};

struct ParentNode_t {
    ChildNode_t node;
    std::vector<ChildNode_t> childs;
    bool collides {false};
    bool ray      {false};
    float x{0},y{0},z{0},
          rot{0};
};

struct RenderComponent_t : public ECS::ComponentBase_t<RenderComponent_t> {
    explicit RenderComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};
    
    float w { 0 }, h { 0 }, d { 0 };

    ParentNode_t entityNodes {};
};