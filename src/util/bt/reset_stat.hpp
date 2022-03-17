#pragma once
#include <iostream>
#include "node.hpp"

struct BTReset_Stat_t : BTNode_t{
    BTReset_Stat_t (IA_Stats stat) : cond{stat} {}

    //Pone los atributos de los states a su valor incial

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::reset_stat;

        if (cond == IA_Stats:: Energia ) { ectx.ia->stamina = 10.0 ;   return BTNodeStatus_t::success;}
        if (cond == IA_Stats:: Cansancio ) { ectx.ia->cansancio = 10.0 ;   return BTNodeStatus_t::success;}
        if (cond == IA_Stats:: Ira  ) { ectx.ia->ira = 10.0 ;   return BTNodeStatus_t::success;}
        return BTNodeStatus_t::fail;
    }

    private:
        IA_Stats    cond { IA_Stats::Energia };

};