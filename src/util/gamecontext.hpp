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
//# GameContext es la clase padre de EntityManager.                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include <vector>
#include "typealiases.hpp"
#include "../cmp/entity.hpp"
namespace ECS{
   struct GameContext_t {
      virtual ~GameContext_t() = default;

      virtual const Entity_t* getEntityByID(EntityID_t eid) const = 0;
      virtual Entity_t* getEntityByID(EntityID_t eid) = 0;

      virtual const Vec_t<Entity_t>& getEntities() const = 0; //solo lectura
      virtual Vec_t<Entity_t>& getEntities() = 0; //lectura y escritura, no es const por eso
   };
}   //namespace ECS