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

#include "stamina.hpp"
#include "../cmp/health.hpp"


template <typename GameCTX_t>
void StaminaSystem_t<GameCTX_t>::update(GameCTX_t& g) const noexcept {
    for(auto& sta : g.template getComponents<StaminaComponent_t>()){
        if(sta.cantStamina!=0){
            sta.cantStamina--;
        }else{
            auto* hea = g.template getRequiredComponent<StaminaComponent_t, HealthComponent_t>(sta);
            if(hea!=nullptr){
                hea->damage = hea->maxHealth;
            }
        }
    }
}