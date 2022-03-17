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
//#     BlackboardComponent es un componente SINGLETON que tienen    #
//#     todas las entidades y contiene informacion del mundo         #
//####################################################################


#pragma once

#include <memory>
#include <vector>

#include "../util/navMesh/NavMesh.hpp"
#include "entity.hpp"
#include "ia.hpp"


struct BlackboardComponent_t {
    

    std::vector<ECS::Entity_t*> palos_bb;        //Array de palos
    std::vector<ECS::Entity_t*> salientes_bb;    //Array de salientes
    std::vector<ECS::Entity_t*> arbustos_bb;     //Array de arbustos*

    ECS::EntityID_t playerID { 0 };             //ID player
    
    double player_tx {0.0}, player_ty {0.0};    //Posicion del target (Player)
    //SB     behaviour {SB::Seek};              //Por defecto es Seek
    bool   tactive = false;                     //Si el behavior esta activo
    bool   player_is_save = false;

    //NavMesh
    //NavMesh navMesh = NavMesh();
};