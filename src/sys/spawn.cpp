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
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#include "spawn.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/render.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/spawner.hpp"
#include <iostream>

template <typename GameCTX_t>
void SpawnSystem_t<GameCTX_t>::update(GameCTX_t& g) const{
    using namespace std::chrono;

    auto now = steady_clock::now();
    for (auto& spw: g.template getComponents<SpawnerComponent_t>()) {

        //getRequiredComponent devuelve un componente a partir de otro
        auto* phy = g.template getRequiredComponent<SpawnerComponent_t, PhysicsComponent_t>(spw);

        if (!phy) { continue; }

        auto passed { now - spw.last_spawn_time };

        if ( spw.to_be_spawned > 0 && passed > spw.spawn_interval ) {
            //spawn

            spw.spawnMethod(spw);
            std::cout << "Spawn:)\n";

            spw.last_spawn_time = now;
            --spw.to_be_spawned;        
        }
    }    
}   