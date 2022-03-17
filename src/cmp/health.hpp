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
//# HealthComponent sirve para guardar los datos necesarios que      #
//#   necesita una entidad para conocer la vida que tiene, el danyo  #
//#   que recibe y da.                                               #
//#                                                                  #
//####################################################################

#pragma once
#include "component.hpp"

struct HealthComponent_t : public ECS::ComponentBase_t<HealthComponent_t> {
    explicit HealthComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    uint64_t selfDamageOnInfliction { 1 }; //daño que me produzco cuando choco
    uint64_t damageInflicted { 0 }; //daño que yo produzco
    uint64_t damage { 0 }; //daño acumulado
    uint64_t health { 1 };
    uint16_t maxHealth { 1 };
    uint16_t hurtCooldown { 0 };
};