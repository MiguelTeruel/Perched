#pragma once
#include "../typealiases.hpp"


enum class goal_types{
    Eat,
    Attack,
    Protect,
    Make_nido
};

struct Goal_t{
    explicit Goal_t(goal_types new_name) : name{new_name} {}
    goal_types name{goal_types::Attack};
    int32_t value{0};

    int32_t getDiscontentment(int32_t newValue){ return newValue * newValue;}

};


struct Action_t{
    explicit Action_t(type_enemy enem,int32_t v_attack, int32_t v_eat, int32_t v_make, int32_t v_protect) :
        belongs_to{enem}, change_attack{v_attack}, change_eat{v_eat}, change_make_nido{v_make}, change_protect{v_protect}{
            setRelatedGoal();
        }

    int32_t id {nextID++};
    static inline int nextID {1};
    
    type_enemy belongs_to       {type_enemy::Aguila};
    goal_types related_goal     {goal_types::Attack};
    int32_t change_attack       {0};
    int32_t change_eat          {0};
    int32_t change_make_nido    {0};
    int32_t change_protect      {0};

    void setRelatedGoal(){
        if(change_attack < 0)       related_goal = goal_types::Attack;
        if(change_eat < 0)          related_goal = goal_types::Eat;
        if(change_make_nido < 0)    related_goal = goal_types::Make_nido;
        if(change_protect < 0)      related_goal = goal_types::Protect;
    }

    int32_t getGoalChange(Goal_t goal){
        if(goal.name == goal_types::Eat)        return change_eat;
        if(goal.name == goal_types::Attack)     return change_attack;
        if(goal.name == goal_types::Make_nido)  return change_make_nido;
        if(goal.name == goal_types::Protect)    return change_protect;
        return -1;
    }

};