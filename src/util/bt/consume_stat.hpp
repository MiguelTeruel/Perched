#pragma once
#include <iostream>
#include "node.hpp"

struct BTConsumeStat_t : BTNode_t{
    BTConsumeStat_t (IA_Stats stat, double flag) : cond{stat},  amount{flag} {}

    //Reduce al stat deseado la cantidad pasada por parametro (Ej: Stamina = Stamina - 50)

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::consume_stat;

        if (cond == IA_Stats:: Energia )        { ectx.ia->stamina -= amount; return BTNodeStatus_t::success;}
        if (cond == IA_Stats:: Cansancio )      { ectx.ia->cansancio -= amount; return BTNodeStatus_t::success;}
        if (cond == IA_Stats:: Ira )            { ectx.ia->ira -= amount; return BTNodeStatus_t::success;}
        return BTNodeStatus_t::fail;
    }

    private:
        IA_Stats    cond { IA_Stats::Energia };
        double      amount { 5.0 };

};