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
//# Game contiene todos los sistemas y se encarga de hacer los       #
//#   updates y de crear el nivel.                                   #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include <iostream>
#include <cstdint>
#include <memory>
#include <thread> 
#include <chrono>
#include <string_view>
#include <vector>

#include "../sys/input.cpp"
#include "../sys/physics.cpp"
#include "../sys/render.cpp"
#include "../sys/colission.cpp"
#include "../sys/ia.cpp"
#include "../sys/spawn.cpp"
#include "../sys/health.cpp"
#include "../sys/camera.cpp"
#include "../sys/text.cpp"
#include "../sys/follow.cpp"
#include "../sys/stamina.cpp"
#include "../sys/sound.cpp"

#include "../cmp/text.hpp"
#include "../cmp/ia.hpp"

#include "../man/state.hpp"
#include "../man/entitymanager.hpp"

#include "../util/gameobjectfactory.hpp"

#include "../util/bt/node.hpp"
#include "../util/bt/ACTarrive.hpp"
#include "../util/bt/ACTseek.hpp"
#include "../util/bt/nodesequence.hpp"
#include "../util/bt/nodeselector.hpp"
#include "../util/bt/checktype.hpp"
#include "../util/bt/behaviourtree.hpp"
#include "../util/bt/change_target_from_init.hpp"
#include "../util/bt/throw_object.hpp"
#include "../util/bt/choose_action.hpp"
#include "../util/bt/check_action.hpp"
#include "../util/bt/apply_goal_value.hpp"
#include "../util/bt/seek_one_axis.hpp"
#include "../util/bt/search_target.hpp"
#include "../util/bt/do_action.hpp"
#include "../util/bt/reset_wait.hpp"
#include "../util/bt/check_see_player.hpp"

#include "../util/gob/goal.hpp"

#include "../util/timer.hpp"

#include "../util/path/Casilla.hpp"
#include "../util/path/pathA.hpp"
#include "../util/path/pathP.hpp"


struct PauseState_t : StateBase_t {
    explicit PauseState_t() = default;

    void update() final {
        std::cout << R"(
            GAME PAUSED:
            [Descansa]
            [PULSA CUALQUIER TECLA PARA VOLVER]
        )";

        int opt;

        std::cin >> opt;
        std::cin.ignore(10000, '\n');
        std::cin.clear();

        m_alive = false;
    }

    bool alive() final {
        return m_alive;
    }

    private:
        bool m_alive { true };
};

struct GameManager_t : StateBase_t {
    explicit GameManager_t(StateManager_t& sm) : SM(sm){
        Render.setDebugDraw(true);

        createLevel1();
    }

    void createActionsIA();

    void update() final { 
        GameTimer_t timer;

        //bucle del juego
        //timedCall( "CAM", [&]() { Camera.update( EntityMan ); } );
        
        bool renderi = Render.update(EntityMan);
        bool inputi = Input.update(EntityMan);
        Physics.update(EntityMan);
        bool iai = IA.update(EntityMan);
        Collision.update(EntityMan);
        Camera.update(EntityMan);
        
        Follow.update(EntityMan);        
        Health.update(EntityMan, Render.getMotor());        
        Spawn.update(EntityMan);
        Stamina.update(EntityMan);
        Text.update(EntityMan);
  
//        auto* phycon = EntityMan.getEntityByID(conejilloindias1)->getComponent<PhysicsComponent_t>();

//        if (phycon) { 
//
//            if(cont2==10){
//                phycon->x = posis.at(cont).x*20;
//                phycon->y = posis.at(cont).y*20;
//        
//                if(cont < posis.size()-1){
//                    cont++;
//                }
//
//                cont2=0;
//            }else{
//                cont2++;
//            }
//        }     

//        if (ruta.size() > 0) {
//            auto* phycon1 = EntityMan.getEntityByID(conejilloindias)->getComponent<PhysicsComponent_t>();
//
//            if (phycon1) { 
//                if(ct2==10){
//                    phycon1->x = ruta[ct].x*20;
//                    phycon1->y = ruta[ct].y*20;
//
//                    if(ct < ruta.size()-1){
//                        ct++;
//                    }
//
//                    ct2=0;
//                }else{
//                    ct2++;
//                }
//            }  
//        }

        timer.waitX_ns(MSPF);

        if (Collision.getMeta(EntityMan) == true) {
            std::cout << "You win\n";
            std::cout << "Crias rescatadas: " << Collision.getCrias(EntityMan) << "\n";

            m_playing = false;
        }

        if (renderi==false || inputi==false || Input.isKeyPressed(keys::KEY_CODE::KEY_ESCAPE)) {
            std::cout << "You lost\n";
            std::cout << "Crias rescatadas: " << Collision.getCrias(EntityMan) << "\n";
            
            m_playing = false;
        }

        if (Input.isKeyPressed(keys::KEY_CODE::KEY_KEY_E)) {
            Collision.addCascada(EntityMan);
            Collision.addArbusto(EntityMan);

            Collision.checkInteractuable(EntityMan);
        } else {
            Collision.resetCascada(EntityMan);
            Collision.resetArbusto(EntityMan);
        }


        if(Input.isKeyPressed(keys::KEY_CODE::KEY_KEY_C)){
            int quesubirbajar = Collision.checkAgujeros(EntityMan);

            if (quesubirbajar != 0) {
                Physics.addTunel(EntityMan);
                Physics.comprobarTunel(quesubirbajar, EntityMan);
            }
        }else{
            Physics.resetTunel(EntityMan);
        }


        //if (Input.isKeyPressed(keys::KEY_CODE::KEY_KEY_P)) {
        //    SM.addState<PauseState_t>();
        //}

        if (Input.isKeyPressed(keys::KEY_CODE::KEY_KEY_J)) {
            Sound.iniciar("event:/Prueba");
        }

        if (Input.isKeyPressed(keys::KEY_CODE::KEY_KEY_L)) {
            Sound.iniciar("event:/Prueba3");
        }

        if (Input.isKeyPressed(keys::KEY_CODE::KEY_KEY_K)) {
            Sound.menos("event:/Prueba3");
        }

        if (Input.isKeyPressed(keys::KEY_CODE::KEY_KEY_I)) {
            Sound.mas("event:/Prueba3");
        }

        Sound.update(EntityMan);
    }

    bool alive() final {
        return m_playing;
    }

    
    void createBT(BehaviourTree_t* tree);

    void createLevel1();

    private:
        static constexpr uint32_t ScreenWidth {1280};
        static constexpr uint32_t ScreenHeight {720};
        static constexpr uint64_t FPS { 60 };
        static constexpr uint64_t MSPF { 1000000000/FPS };

        ECS::EntityManager_t EntityMan;


        BehaviourTree_t tree1;

        std::vector<Action_t> action_container;

        //Creacion de sistemas
        const RenderSystem_t<ECS::EntityManager_t> Render{ScreenWidth,ScreenHeight};
        InputSystem_t<ECS::EntityManager_t> Input {Render.getMotor()};
        PhysicsSystem_t<ECS::EntityManager_t> Physics {};
        ColissionSystem_t<ECS::EntityManager_t> Collision{0, 0, 0, 0};
        SpawnSystem_t<ECS::EntityManager_t> Spawn {};
        CameraSystem_t<ECS::EntityManager_t> Camera {};
        const HealthSystem_t<ECS::EntityManager_t> Health {};
        TextSystem_t<ECS::EntityManager_t> Text {};
        FollowSystem_t<ECS::EntityManager_t> Follow {};
        StaminaSystem_t<ECS::EntityManager_t> Stamina{};
        GameObjectFactory_t GOFact { EntityMan , Render.getMotor()};
        IASystem_t<ECS::EntityManager_t> IA {&GOFact};
        SoundSystem_t<ECS::EntityManager_t> Sound {};
        
        bool m_playing { true };
        StateManager_t& SM;

        PathP_t PathP{75, 45};
        PathA_t PathA{};
        std::vector<Casilla> posis;
        std::vector<Casilla> ruta;
        ECS::EntityID_t conejilloindias{0};
        ECS::EntityID_t conejilloindias1{0};
        int cont {0}, cont2 {0}, ct {0}, ct2 {0};
};