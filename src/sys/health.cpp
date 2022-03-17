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

#include "health.hpp"

template <typename GameCTX_t>
constexpr bool HealthSystem_t<GameCTX_t>::leafNodeCollided(const BoundingBoxNode_t& bn) const noexcept {
    return bn.collided;
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::deleteNodes(GameCTX_t& g, const HealthComponent_t& he, Motor3D* motor) const noexcept {
    auto* ren = g.template getRequiredComponent<HealthComponent_t, RenderComponent_t>(he);

    if (!ren) { return; }

    motor->removeNode(ren->entityNodes.node.node);

    if (!ren->entityNodes.childs.empty()) {
        for (auto i=0; i<ren->entityNodes.childs.size(); i++) {
            motor->removeNode(ren->entityNodes.childs.at(i).node);
        }        
    }

    //std::cout << "Entity " << he.getEntityID() << " is dead1!\n";
    g.destroyEntityByID(he.getEntityID());
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::checkControl(GameCTX_t& g, HealthComponent_t& he, Motor3D* motor) const noexcept {
    auto* c { g.template getRequiredComponent<HealthComponent_t, ColliderComponent_t>(he) };

    if (c->properties & ColliderComponent_t::P_IsPlayer) {

        auto* ct { g.template getRequiredComponent<HealthComponent_t, ControlComponent_t>(he) };

        if (ct != nullptr) {
            if (ct->puntosControl.size() == 0) {
                deleteNodes(g, he, motor); 
            } else {
                he.health = he.maxHealth;
                
                auto* phy { g.template getRequiredComponent<HealthComponent_t, PhysicsComponent_t>(he) };

                bool encontrado { false };
                int resta { 0 };

                while (encontrado == false) {
                    auto id = ct->puntosControl.back() - resta;

                    const auto* punC = g.getEntityByID(id);

                    auto* phyC = punC->template getComponent<PhysicsComponent_t>();

                    if (phyC->y > phy->y) {
                        resta++;
                    } else {
                        phy->x = phyC->x;
                        phy->y = phyC->y;

                        auto* ren { g.template getRequiredComponent<HealthComponent_t, RenderComponent_t>(he) };

                        if (ren != nullptr && !ren->entityNodes.childs.empty()) {
                            for (auto i=0; i<ren->entityNodes.childs.size(); i++) {
                                ren->entityNodes.childs.at(i).x = phy->x + ren->entityNodes.childs.at(i).disx;
                                ren->entityNodes.childs.at(i).y = phy->y + ren->entityNodes.childs.at(i).disy;
                                ren->entityNodes.childs.at(i).z = phy->z + ren->entityNodes.childs.at(i).disz;
                            }
                        }

                        encontrado = true;
                    }
                }

                auto* est { g.template getRequiredComponent<HealthComponent_t, StaminaComponent_t>(he) };

                if(est!=nullptr){
                    est->cantStamina = est->maxStamina;
                }
            }  
        }     
    } else {
        if (c->properties != ColliderComponent_t::P_Enemy) {
            deleteNodes(g, he, motor);
        }
    }
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::update(GameCTX_t& g, Motor3D* motor) const noexcept {
    for(auto& he: g.template getComponents<HealthComponent_t>()){
        if (he.damage) {
            //std::cout << "Entity " << he.getEntityID() << " damage " << he.damage << " vida " << he.health <<"\n";
            
            if (he.damage < he.health) {
                he.health -= he.damage;
            } else {
                he.health = 0;

                checkControl(g, he, motor);
            }

            he.damage = 0;
        }

        auto* re { g.template getRequiredComponent<HealthComponent_t, RenderComponent_t>(he) };
        auto* c { g.template getRequiredComponent<HealthComponent_t, ColliderComponent_t>(he) };

        if (!c) { continue; }

      /*  if (c->properties == ColliderComponent_t::P_IsPlayer ){
            auto blanco = std::unique_ptr<Texture>(motor->getTexture("assets/textures/cuadroblanco.jpg"));
            re->entityNodes.node.node->setMaterialTexture(blanco.get());

            for (int i=0 ; i < re->entityNodes.childs.size() ; i++){
                re->entityNodes.childs.at(i).node->setMaterialTexture(blanco.get());
            }

            if(! he.hurtCooldown == 0 ){ 
                he.hurtCooldown--; 
                auto red = std::unique_ptr<Texture>(motor->getTexture("assets/textures/red.png"));
                re->entityNodes.node.node->setMaterialTexture(red.get());

                for ( int i=0 ;i < re->entityNodes.childs.size(); i++){
                    re->entityNodes.childs.at(i).node->setMaterialTexture(red.get());
                }
            }
        } */

        for (auto& box: c->boxes) {
            if (he.health && leafNodeCollided(box)) {
                if (--he.health == 0) {
                    checkControl(g, he, motor);
                }

                box.collided = false;
            }
        }
    }
}   