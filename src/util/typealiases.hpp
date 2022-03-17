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
//# Alias para algunos tipos de c++, para no tener en las clases     #
//#   mucho texto para el tipo, e identificarlos rapidamente.        #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include <vector>
#include <unordered_map>
#include <memory>

namespace ECS {
    template<typename T>
    using Vec_t = std::vector<T>;

    template<typename KEY_t, typename VALUE_t>
    using Hash_t = std::unordered_map<KEY_t, VALUE_t>;

    template<typename T>
    using UPtr = std::unique_ptr<T>;
    
    using EntityID_t = std::size_t;
    using ComponentID_t = std::size_t;
    using ComponentTypeID_t = std::size_t;
};

enum class objects_type{
    Telaranya,
    Palo,
    Saliente,
    Arbusto,
    Ninguno
};

enum class type_enemy{
    Aguila,
    Aranya,
    Cabra
};

enum class type_action{
    Comer,
    Dormir,
    Descansar,
    Atacar,
    Vigilar,
};

enum class BTState{
    default_state,
    ACTarrive,
    ACTseek,
    applygoal,
    change_target_init,
    check_action,
    check_distance_target,
    check_player_save,
    check_see_player,
    check_stat_over,
    check_stat_under,
    check_type,
    choose_action,
    consume_stat,
    do_action,
    reset_stat,
    reset_wait,
    search_target,
    seek_one_axis,
    take_object,
    throw_object
};