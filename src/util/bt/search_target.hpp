#pragma once
#include <iostream>
#include <math.h>
#include "node.hpp"
#include "../typealiases.hpp"




struct BTSearchTarget_t : BTNode_t{
    BTSearchTarget_t (objects_type tipo) : type{tipo} {}

    //Dependiendo de los parametros pasados, la IA decidira si ir hacia el target o no

    bool actualizarPos(EntityContext_t &ectx, std::vector<ECS::Entity_t*>& vector){
        float x, y = 0;
        float actualX, actualY, distance = 0;
        float minorDistance = 500;

        if(vector.empty()){
            return false;
        }

        for(int i = 0; i < vector.size(); i++){
            auto compo_pal = vector[i]->getComponent<PhysicsComponent_t>();
            
            if(!compo_pal){continue;}

            x = compo_pal->x;
            y = compo_pal->y;

            actualX = std::abs(x - ectx.phy->x);
            actualY = std::abs(y - ectx.phy->y);

            distance = std::sqrt((actualX*actualX)+(actualY*actualY));

            if(distance < minorDistance){
                minorDistance = distance;
                //std::cout<<"encontre algo en x: "<<x<<"e y: "<<y<<"\n";
                xt = x;
                yt = y;
            }
        }

        if (minorDistance < 500) return true;
        return false;
    }

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::search_target;

        switch(type){
            case objects_type::Palo:
                {
                    auto& palos = ectx.bb->palos_bb;
                    bool actualizado = actualizarPos(ectx, palos);
                    //auto actualizado = actualizarPos(ectx, objects_type::Palo);
                    if(!actualizado) return BTNodeStatus_t::fail;
                    ectx.ia->tx = xt;
                    ectx.ia->ty = yt;
                    return BTNodeStatus_t::success;
                }
            break;

            case objects_type::Saliente:
                {
                    auto& salientes = ectx.bb->salientes_bb;
                    bool actualizado = actualizarPos(ectx, salientes);
                    //auto actualizado = actualizarPos(ectx, objects_type::Saliente);
                    if(!actualizado) return BTNodeStatus_t::fail;
                    ectx.ia->tx = xt;
                    ectx.ia->ty = yt;
                    //std::cout << "Saliente encontrado en X: " << xt << "; Y: " << yt << std::endl;
                    return BTNodeStatus_t::success;
                }
            break;

            case objects_type::Arbusto:
                {
                    auto& arbustos = ectx.bb->arbustos_bb;
                    bool actualizado = actualizarPos(ectx, arbustos);
                    //auto actualizado = actualizarPos(ectx, objects_type::Arbusto);
                    if(!actualizado) return BTNodeStatus_t::fail;
                    ectx.ia->tx = xt;
                    ectx.ia->ty = yt;
                    return BTNodeStatus_t::success;
                }
            break;
        }
        return BTNodeStatus_t::fail;
    };

    private:
        objects_type type { objects_type::Ninguno };
        float xt, yt { 0 };
};

/*
    bool actualizarPos(EntityContext_t &ectx, objects_type type){
        float x, y = 0;
        float actualX, actualY, distance = 0;
        float minorDistance = -1;
        if(type == objects_type::Palo){
            if(ectx.bb->palos_bb.empty()){
                return false;
            }
            for(int i = 0; i < ectx.bb->palos_bb.size(); i++){
                auto *compo_pal = ectx.bb->palos_bb[i].getComponent<PhysicsComponent_t>();
                if(!compo_pal){continue;}
                x = compo_pal->x;
                y = compo_pal->y;
                actualX = std::abs(x - ectx.phy->x);
                actualY = std::abs(y - ectx.phy->y);
                distance = std::sqrt((actualX*actualX)+(actualY*actualY));
                if(distance < minorDistance | minorDistance == -1){
                    minorDistance = distance;
                }
            }
            return true;
        }
        
        if(type == objects_type::Saliente){
            if(ectx.bb->salientes_bb.empty()){
                return false;
            }
            for(int i = 0; i < ectx.bb->salientes_bb.size(); i++){
                
                auto *compo_sal = ectx.bb->salientes_bb[i].getComponent<PhysicsComponent_t>();
                if(!compo_sal){continue;}
                x = compo_sal->x;
                y = compo_sal->y;
                actualX = std::abs(x - ectx.phy->x);
                actualY = std::abs(y - ectx.phy->y);
                distance = std::sqrt((actualX*actualX)+(actualY*actualY));
                if(distance < minorDistance | minorDistance == -1){
                    minorDistance = distance;
                    xt = x;
                    yt = y;
                }
            }
            return true;
        }
        if(type == objects_type::Arbusto){
            if(ectx.bb->arbustos_bb.empty()){
                return false;
            }
            for(int i = 0; i < ectx.bb->arbustos_bb.size(); i++){
                
                auto *compo_arb = ectx.bb->arbustos_bb[i].getComponent<PhysicsComponent_t>();
                if(!compo_arb){continue;}
                x = compo_arb->x;
                y = compo_arb->y;
                actualX = std::abs(x - ectx.phy->x);
                actualY = std::abs(y - ectx.phy->y);
                distance = std::sqrt((actualX*actualX)+(actualY*actualY));
                if(distance < minorDistance | minorDistance == -1){
                    minorDistance = distance;
                    xt = x;
                    yt = y;
                }
            }
            return true;
        }
        return true;
    };
*/