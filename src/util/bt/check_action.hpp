#pragma once
#include <iostream>
#include "node.hpp"

struct BTCheck_Action_t : BTNode_t{
    BTCheck_Action_t ( type_enemy enem, goal_types goal ) :  this_enem{enem}, this_goal{goal} {}

    //Comprueba si la IA esta a X distancia del target

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::check_action;
        
        if(ectx.ia->action_chosen->belongs_to == this_enem && ectx.ia->action_chosen->related_goal == this_goal ){
            return BTNodeStatus_t::success;   
        } 

        return BTNodeStatus_t::fail;
    }

    private:
        type_enemy this_enem {type_enemy::Aguila};
        goal_types this_goal {goal_types::Attack};

};