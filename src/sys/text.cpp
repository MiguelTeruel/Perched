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

#include "text.hpp"
#include "../cmp/text.hpp"
#include "../cmp/entity.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/control.hpp"
#include "../cmp/health.hpp"
#include "../cmp/puntos.hpp"
#include "../cmp/stamina.hpp"
template <typename GameCTX_t>
void TextSystem_t<GameCTX_t>::update(GameCTX_t& g) const noexcept {
    for(auto& tex : g.template getComponents<TextComponent_t>()){
        for (auto& textis : tex.texts.childs) {

            if ((textis.parteFija).find("Control") != std::string::npos) {
                ControlComponent_t* player = nullptr;

                for(auto& col : g.template getComponents<ColliderComponent_t>()) {
                    if (col.properties & ColliderComponent_t::P_IsPlayer) {
                        player = g.template getRequiredComponent<ColliderComponent_t, ControlComponent_t>(col);
                        continue;
                    }
                }

                if (player != nullptr) {
                    std::string text = "";
                    for (auto& ct : player->puntosControl) {
                        text = text + " " + std::to_string(ct);
                    }

                    textis.parteFija = "Control : " + text;
                }
            } else {
                if ((textis.parteFija).find("Vidas") != std::string::npos) {
                    HealthComponent_t* player = nullptr;

                    for(auto& col : g.template getComponents<ColliderComponent_t>()) {
                        if (col.properties & ColliderComponent_t::P_IsPlayer) {
                            player = g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(col);
                            continue;
                        }
                    }

                    if (player != nullptr) {
                        textis.parteFija = "Vidas : " + std::to_string(player->health);
                    }
                } else {
                    if ((textis.parteFija).find("Puntos") != std::string::npos) {
                        PuntosComponent_t* player = nullptr;

                        for(auto& col : g.template getComponents<ColliderComponent_t>()) {
                            if (col.properties & ColliderComponent_t::P_IsPlayer) {
                                player = g.template getRequiredComponent<ColliderComponent_t, PuntosComponent_t>(col);
                                continue;
                            }
                        }

                        if (player != nullptr) {
                            textis.parteVariable = player->puntos;
                        }
                    } else {
                        if((textis.parteFija).find("Stamina") != std::string::npos){
                             StaminaComponent_t* player = nullptr;

                        for(auto& col : g.template getComponents<ColliderComponent_t>()) {
                            if (col.properties & ColliderComponent_t::P_IsPlayer) {
                                player = g.template getRequiredComponent<ColliderComponent_t, StaminaComponent_t>(col);
                                continue;
                            }
                        }

                        if (player != nullptr) {
                            textis.parteVariable = player->cantStamina;
                        }
                        }else{
                            textis.parteVariable++;
                        }
                        
                    }                    
                }                
            }
        }
    }
} 