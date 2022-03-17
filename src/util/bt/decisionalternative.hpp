#pragma once
#include <iostream>
#include "node.hpp"

struct BTDecisionAlternative_t : BTNode_t{
    BTDecisionAlternative_t (bool a = false) : alternative{a} {}

    //Permite a la IA no siempre ejecutar el mismo arbol en el mismo orden para darle variedad

    BTNodeStatus_t run(EntityContext_t &) noexcept final{
        alternative = !alternative;
        if (alternative) return BTNodeStatus_t::success;
        return BTNodeStatus_t::fail;
    }

    private:
        bool  alternative { false };

};