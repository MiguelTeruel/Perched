#pragma once
#include <iostream>
#include "node.hpp"

struct BTCheckStatUnder_t : BTNode_t{
    BTCheckStatUnder_t (IA_Stats stat, double flag) : cond{stat},  mark{flag} {}

    //Comprueba si stat que se va a comprobar (stamina, cansancio o ira) en el enemigo es menor que lo que se ha pasado como parametro

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::check_stat_under;

        if (cond == IA_Stats:: Energia && ectx.ia->stamina < mark ) { return BTNodeStatus_t::success;}
        if (cond == IA_Stats:: Cansancio && ectx.ia->cansancio < mark ) { return BTNodeStatus_t::success;}
        if (cond == IA_Stats:: Ira && ectx.ia->ira < mark ) { return BTNodeStatus_t::success;}
        return BTNodeStatus_t::fail;
    }

    private:
        IA_Stats    cond { IA_Stats::Energia };
        double      mark { 5.0 };

};