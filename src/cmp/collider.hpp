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
//# ColliderComponent sirve para guardar los datos necesarios que    #
//#   necesita una entidad para saber con que colisiona, que tipo    #
//#   de entidad es y como son sus bounding boxes.                   #
//#                                                                  #
//####################################################################

#pragma once
#include "component.hpp"

template <typename Data_t>
struct BoundingBox_t {
    Data_t xLeft {0}, xRight {0};
    Data_t yUp {0}, yDown {0};
    Data_t zFront {0}, zBack {0};
};

struct BoundingBoxNode_t {
    BoundingBox_t<float> box;
    bool collided { false };
    
    float disX { 0 }, disY { 0 };
    bool lanzadorrocas { false };
};

struct ColliderComponent_t : public ECS::ComponentBase_t<ColliderComponent_t> {
    explicit ColliderComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    enum {
        P_Nothing = 0x00,
        P_IsPlayer = 0x01,
        P_IsSolid = 0x02,
        P_Damages = 0x04,
        P_Arbusto = 0x08,
        P_Control = 0x10,
        P_Semilla = 0x12,
        P_Nido = 0x14,
        P_Cria = 0x16,      
        P_PlanoS = 0x18,
        P_Agujero = 0x20,
        P_Trampolin = 0x22,
        P_Saliente = 0x24,
        P_Accelerate = 0x26,
        P_Cascada = 0x28,
        P_Deccelerate = 0x30,
        P_Meta = 0x32,
        P_Enemy = 0x34,
        P_EnemyVisual = 0x36,
        P_Telaranya = 0x38
    };

    uint16_t properties { P_Nothing };
    
    std::vector<BoundingBoxNode_t> boxes {};

    bool cercaArbusto { false };
    bool nomover { true };

    uint8_t subirbajar { 0 };
    uint8_t quesubirbajar { 0 };
};