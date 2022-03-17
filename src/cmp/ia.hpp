//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//# IAComponent sirve para guardar los datos necesarios que          #
//#   necesita una entidad para poder realizar movimientos acorde a  #
//#   su situaacion actual                                           #
//#                                                                  #
//####################################################################

#pragma once
#include "component.hpp"
#include "../util/typealiases.hpp"
#include "../util/gob/goal.hpp"
#include "../util/path/Casilla.hpp"

struct BehaviourTree_t;
struct BTNode_t;

enum class SB{
    Arrive,
    Seek,
};

struct IAComponent_t : public ECS::ComponentBase_t<IAComponent_t> {
    using value_type        = BTNode_t*;
    using container_type    = std::vector<value_type>;
    using iterator          = std::vector<value_type>::iterator;

    explicit IAComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {
        my_goals.emplace_back(Goal_t(goal_types::Eat));
        my_goals.emplace_back(Goal_t(goal_types::Attack));
        my_goals.emplace_back(Goal_t(goal_types::Protect));
        my_goals.emplace_back(Goal_t(goal_types::Make_nido));
    };

    double      tx { 200 }, ty { 150 }; // Target direction
    double      ix { 0 }, iy { 0 }; // Inicial position
    double      arrivalRadius { 1 };
    double      time2arrive { 5 };
    bool        tactive { true };

    BehaviourTree_t *tree{nullptr};
    std::unordered_map <BTNode_t*, iterator> running_node ;

    double wait{200.0};
    double max_wait{200.0};


    double    stamina;
    double    cansancio;
    double    ira;

    type_enemy enemy { type_enemy::Aguila };

    objects_type my_object { objects_type::Ninguno };
    bool my_object_to_follow {false };

    std::vector<Goal_t> my_goals{};

    Action_t * action_chosen{nullptr};

    bool visto {false};

    BTState estadoIA { BTState::default_state };

    bool pathplaneo {false};
    double time2arrivePath { 0.5 };
    double arrivalRadiusPath { 0.0 };
    int indiceRuta {0};
    std::vector<Casilla> ruta;
};