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

#include "ia.hpp"



template <typename GameCTX_t>
bool IASystem_t<GameCTX_t>::update(GameCTX_t& g) const{


    //Obtener el component Blackboard
    BlackboardComponent_t& bb { g.template getBlackBoard() };

    for(auto& ia: g.template getComponents<IAComponent_t>()){

        
        auto* phy = g.template getRequiredComponent<IAComponent_t, PhysicsComponent_t>(ia);
        auto* hea = g.template getRequiredComponent<IAComponent_t, HealthComponent_t>(ia);
        //std::cout<<"Mi ID: "<<ia.getEntityID()<<"Mi vida: "<<hea->selfDamageOnInfliction<<"\n";

        if(!phy) {return false;}
        if (ia.tree){

            EntityContext_t ectx {g.template getEntityByID(ia.getEntityID()) , &ia, phy, &bb};
            ia.tree->run(ectx);

            if(ia.my_object == objects_type::Palo) {
                ia.my_object = objects_type::Ninguno;
                my_gof->unfollowPalo(ia.getEntityID());
            }

            if(ia.my_object == objects_type::Telaranya) {
                ia.my_object = objects_type::Ninguno;
                auto vel {0};
                if(phy->x < bb.player_tx){
                    vel = 1;
                }else{
                    vel = -1;
                }
                my_gof->createTelaranya(phy->x-2, phy->y-2, vel);
            }

            if(ia.my_object_to_follow){
                ia.my_object_to_follow = false;
                my_gof->createPalo(phy->x, phy->y, 1, ia.getEntityID());
            }
        }
        ia.visto = false;
    }


    return true;
}      

// template <typename GameCTX_t>
// bool IASystem_t<GameCTX_t>:: arrive(IAComponent_t * iart, PhysicsComponent_t * phy) const{
// 
//     if (!iart->tactive) return false;
// 
// 
//     auto vtx { iart->tx - phy->x };
//     auto vty { iart->ty - phy->y };
// 
//     auto vtlin { std::sqrt(vtx*vtx + vty*vty) };
//     if (vtlin < iart->arrivalRadius){
//     //    iart->tactive = false;
//         return true;
//     }
//     phy->v_linear = std::clamp( vtlin / iart->time2arrive, -phy->KmaxVLin, phy->KmaxVLin );
// 
// 
//     auto torient{ std::atan2(vty, vtx) };
//     if ( torient < 0 ) torient += 2*PI;
//     auto vang { torient - phy->orientation };
//     if ( vang > PI ) vang -= 2*PI;
//     else if ( vang < -PI ) vang += 2*PI;
//     phy->v_angular = std::clamp( vang / iart->time2arrive, -phy->KmaxVang, phy->KmaxVang );
//     return false;
// }     
// 
// 
// template <typename GameCTX_t>
// bool IASystem_t<GameCTX_t>:: seek(IAComponent_t * iart, PhysicsComponent_t * phy) const{
// 
//     if (!iart->tactive) return false;
// 
// 
//     auto vtx { iart->tx - phy->x };
//     auto vty { iart->ty - phy->y };
// 
//     auto vtlin { std::sqrt(vtx*vtx + vty*vty) };
//     
//     
// 
//     auto torient{ std::atan2(vty, vtx) };
//     if ( torient < 0 ) torient += 2*PI;
// 
// 
//     auto angular_distance { torient - phy->orientation };
//     if ( angular_distance > PI ) angular_distance -= 2*PI;
//     else if ( angular_distance < -PI ) angular_distance += 2*PI;
//     auto angular_velocity { angular_distance / iart->time2arrive };
//     phy->v_angular = std::clamp( angular_velocity, -phy->KmaxVang, phy->KmaxVang );
// 
//     phy->v_linear = (phy->KmaxVLin / (1 + std::fabs(angular_velocity)));
//     return false;
// }