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
//# SpawnerComponent sirve para guardar los datos necesarios que     #
//#   necesita una entidad que es spawn para saber que entidades     #
//#   spawnea y cada cuanto tiempo.                                  #
//#                                                                  #
//####################################################################

#pragma once
#include <cstdint>
#include <chrono>
#include <functional>
#include "component.hpp"

using namespace std::chrono_literals;

struct SpawnerComponent_t : public ECS::ComponentBase_t<SpawnerComponent_t> {
    using clk = std::chrono::steady_clock;

    explicit SpawnerComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    std::function<void(const SpawnerComponent_t&)> spawnMethod {};

    clk::time_point last_spawn_time { clk::now() };
    std::chrono::duration<double> spawn_interval { 5s };

    //numero de entidades a spawnear
    std::size_t to_be_spawned { 2 };
};