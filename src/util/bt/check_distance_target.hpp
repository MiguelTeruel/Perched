#pragma once
#include <iostream>
#include <cmath>
#include "node.hpp"

struct BTCheck_Distance_Target_t : BTNode_t{
    BTCheck_Distance_Target_t ( double flag) :  distance{flag} {}

    //Comprueba si la IA esta a X distancia del target

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::check_distance_target;

        double disx = std::abs( ectx.phy->x - ectx.ia->tx );
        double disy = std::abs( ectx.phy->y - ectx.ia->ty );
        double dis_lin = sqrt( disx*disx + disy*disy );
        if( dis_lin < distance ) return BTNodeStatus_t::success;

        return BTNodeStatus_t::fail;
    }

    private:
        double      distance { 100.0 };

};