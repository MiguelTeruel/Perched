#pragma once
#include <iostream>
#include "node.hpp"
#include "../typealiases.hpp"


struct BTTakeObject_t : BTNode_t{
    BTTakeObject_t () {}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::take_object;

        //Crear el palo y hacer que este siga al aguila
        ectx.ia->my_object_to_follow = true;
    }

    private:
};