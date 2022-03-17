#pragma once
#include <iostream>
#include "node.hpp"
#include "../typealiases.hpp"

    //Se comprueba si el player esta en una posicion save 

struct BT_Check_Save_Player_t : BTNode_t{
    BT_Check_Save_Player_t (){}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::check_player_save;

        if(!ectx.bb->player_is_save){
            return BTNodeStatus_t::success;
        }
        return BTNodeStatus_t::fail;
    };
};