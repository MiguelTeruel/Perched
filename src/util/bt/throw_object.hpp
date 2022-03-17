#pragma once
#include <iostream>
#include "node.hpp"
#include "../typealiases.hpp"


struct BTThrowObject_t : BTNode_t{
    BTThrowObject_t (objects_type tipo) : crear{tipo} {}

    //Comprueba si stat que se va a comprobar (stamina, cansancio o ira) en el enemigo es menor que lo que se ha pasado como parametro

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::throw_object;

        switch(crear){
            case objects_type::Telaranya:
                ectx.ia->my_object = objects_type::Telaranya;
                return BTNodeStatus_t::success;
            break;
            
            case objects_type::Palo:
                ectx.ia->my_object = objects_type::Palo;
                return BTNodeStatus_t::success;
            break;
        }
        return BTNodeStatus_t::fail;
    }

    private:
        objects_type crear {};
};

/*
        if(crear == objects_type::Telaranya){ectx.ia->my_object = objects_type::Telaranya;}
        if(crear == objects_type::Palo){ ectx.ia->my_object = objects_type::Palo;}
        return BTNodeStatus_t::success;
*/