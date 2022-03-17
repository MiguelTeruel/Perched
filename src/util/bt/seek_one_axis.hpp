#pragma once
#include <iostream>
#include "node.hpp"
#include "../typealiases.hpp"
#include "../stbe/Steering.hpp"

struct BTSeekOneAxis_t : BTNode_t{
    BTSeekOneAxis_t (){}

    //Comprueba si el player se encuentra cerca de la IA

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::seek_one_axis;

        //Comprobar si el blackboard tiene target, que entonces significa que si ha visto al enemigo
        if(ectx.ia->wait > 0){
            Point2D_t target{ectx.bb->player_tx, ectx.phy->y};
            //std::cout<<"target x: "<<target.x<<" , target y: "<<target.y<<"\n";
            //std::cout<<"Mi pos x: "<<ectx.phy->x<<" , Mi pos y: "<<ectx.phy->y<<"\n";

            auto st = STBEH::seek_one(ectx.phy, &target, ectx.ia->time2arrive, ectx.ia->arrivalRadius);

            ectx.phy->v_linear= st.linear;
            ectx.phy->v_angular= st.angular;

            ectx.ia->wait--;

            return BTNodeStatus_t::running;
        }else{
            return BTNodeStatus_t::success;
        }
    }

    private:
};