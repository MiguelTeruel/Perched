#pragma once
#include <iostream>
#include "node.hpp"
#include "../typealiases.hpp"

    //Nodo INCOMPLETO, TENDRA USO CUANDO SE AÑADAN LAS ANIMACIONES

struct BT_Do_Action_t : BTNode_t{
    BT_Do_Action_t (type_action act, int tim) : action{act}, time{tim}{}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::do_action;

        switch(action){
            case type_action::Atacar:
                //Do ATACAR animation
                return BTNodeStatus_t::success;
            break;

            case type_action::Comer:
                //Do COMER animation
                return BTNodeStatus_t::success;
            break;

            case type_action::Descansar:
                //Do DESCANSAR animation
                return BTNodeStatus_t::success;
            break;

            case type_action::Dormir:
                //Do DORMIR animation
                return BTNodeStatus_t::success;
            break;

            case type_action::Vigilar:
                //Do VIGILAR animation
                return BTNodeStatus_t::success;
            break;
        }
        return BTNodeStatus_t::fail;
    };

    private:
        type_action action;
        int time;
};

/*
    if(action == type_action::Atacar){
            //Do ATACAR animation
            return BTNodeStatus_t::success;
        }
        if(action == type_action::Comer){
            //Do COMER animation
            return BTNodeStatus_t::success;
        }
        if(action == type_action::Descansar){
            //Do DESCANSAR animation
            return BTNodeStatus_t::success;
        }
        if(action == type_action::Dormir){
            //Do DORMIR animation
            return BTNodeStatus_t::success;
        }
        if(action == type_action::Vigilar){
            //Do VIGILAR animation
            return BTNodeStatus_t::success;
        }
*/