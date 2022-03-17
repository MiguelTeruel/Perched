#pragma once
#include <iostream>
#include "node.hpp"
#include "../typealiases.hpp"




struct BTChooseAction_t : BTNode_t{
    BTChooseAction_t (std::vector<Action_t> *actions) : all_actions{actions} {}

    //Dependiendo de los parametros pasados, la IA decidira si ir hacia el target o no
    
    Action_t* chooseAction(EntityContext_t &ectx, std::vector<Action_t*> type_actions){
        ectx.ia->estadoIA = BTState::choose_action;
        
        if (type_actions.empty()) return nullptr;

        Action_t* bestAction = *type_actions.begin();
        int32_t bestValue = calculateDiscontentment(*type_actions.begin(), &ectx.ia->my_goals);

        for (auto &act: type_actions){
            int32_t thisValue  = calculateDiscontentment(act, &ectx.ia->my_goals);
            if(thisValue < bestValue){
                bestValue = thisValue;
                bestAction = act;
            }
        }
       return bestAction;

    };


    int32_t calculateDiscontentment(Action_t* act, std::vector<Goal_t>* goals){
        int32_t descontento = 0;

        for (auto &goal: *goals){
            int32_t goal_result_act = act->getGoalChange(goal);
            if(goal_result_act < 0) goal_result_act = 0;

            goal_result_act = goal.getDiscontentment(goal.value + goal_result_act);
            descontento += goal_result_act;
        }
        return descontento;
    };

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        if(all_actions->empty()) return BTNodeStatus_t::fail;

        std::vector<Action_t*> type_actions;
        for (auto &act: *all_actions){
            if(act.belongs_to == ectx.ia->enemy){
                type_actions.emplace_back(&act);
            }

        }
        ectx.ia->action_chosen = chooseAction(ectx, type_actions);
        if(ectx.ia->action_chosen) return BTNodeStatus_t::success;
        return BTNodeStatus_t::fail;

    };

    private:
        std::vector<Action_t>* all_actions;
};