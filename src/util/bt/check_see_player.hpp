#pragma once
#include <iostream>
#include "node.hpp"
#include "../typealiases.hpp"

    //Se comprueba si el player esta en una posicion save 

struct BT_Check_See_Player_t : BTNode_t{
    BT_Check_See_Player_t (){}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::check_see_player;
        
        if(ectx.ia->visto){
            //std::cout<<" x: "<< ectx.bb->player_tx<<" y: "<< ectx.bb->player_ty<<"\n";
            return BTNodeStatus_t::success;
        }
        return BTNodeStatus_t::fail;
    };
};