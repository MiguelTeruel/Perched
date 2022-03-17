#pragma once
#include <iostream>
#include "node.hpp"

struct BTCheckType_t : BTNode_t{
    BTCheckType_t (type_enemy condi) : type{condi} {}

    //Comprueba el tipo de enemigo que es la IA
    //Se usa para saber por que rama del BT hay que ir

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::check_type;

        if (ectx.ia->enemy == type) { return BTNodeStatus_t::success;}
        return BTNodeStatus_t::fail;
    }

    private:
        type_enemy  type { type_enemy::Aguila };

};