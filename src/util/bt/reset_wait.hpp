#pragma once
#include <iostream>
#include "node.hpp"

struct BTResetWait_t : BTNode_t{
    BTResetWait_t () {}

    //Pone los atributos de los states a su valor incial

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::reset_wait;

        ectx.ia->wait = ectx.ia->max_wait;
        return BTNodeStatus_t::success;
    }


};