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

#include "camera.hpp"


template <typename GameCTX_t>
constexpr void CameraSystem_t<GameCTX_t>::update(GameCTX_t& g) const noexcept {
    for(auto& cam: g.template getComponents<CameraComponent_t>()){
        auto* entity { g.getEntityByID(cam.followEntityID) };
        if (!entity) { continue; }

        auto* entPhy { entity->template getComponent<PhysicsComponent_t>() };
        if (!entPhy) { continue; }

        //cam.camNode->setPosition(entPhy->x, entPhy->y-40, -40);
        //cam.camNode->setTarget(entPhy->x, entPhy->y, 0);
        
       cam.camNode->setPosition(Vector3d(entPhy->x, entPhy->y, 85));
     // cam.camNode->setTarget(Vector3d(entPhy->x, entPhy->y, 15));
    }
} 