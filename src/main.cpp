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
//# Main sirve para ejecutar el juego y detenerlo cuando ya no hay   #
//#   estados del juego vivos.                                       #
//#                                                                  #
//#                                                                  #
//####################################################################
#include "Motor3D/Motor3DLUM/Motor3DLUM.hpp"
#include "man/game.hpp"
#include "man/state.hpp"
#include <iostream>
#include <memory>

struct MenuState_t : StateBase_t {
    explicit MenuState_t(StateManager_t& sm) : SM(sm) {}

    void update() final {
        std::cout << R"(
            MENU:
            1. Play
            2. Credits
            -. Exit
        )";

        int opt;

        std::cin >> opt;

        switch (opt) {
            case 1: SM.addState<GameManager_t>(SM); break;
            case 2: credits(); break;
            default: m_alive = false;
        }
    }

    bool alive() final {
        return m_alive;
    }

    void credits() {
        std::cout << R"(
            CREDITS:
            1. Paula Garcia Morales
            2. Laura Gil Lopez
            3. Jorge Perez Dominguez
            4. Alba Ruiz Maiques
            5. Javier Sibada Lopez
            6. Miguel Teruel Carvajal
            -. Exit
        )";
    }

    private:
        bool m_alive { true };
        StateManager_t& SM;
};

int main(){
    try {
        StateManager_t States;
        States.addState<MenuState_t>(States);

        while (States.alive()) {
            States.update();
        }    
    } catch (std::exception& e) {
        std::cout << "[[ EXCEPTION ]]: " << e.what() << "\n\n";
    } catch(...){
        std::cout << "Capturada : \n";
    }
}
    /* Pruebas con nodos */
    /*Node* camera = m.createCamera(Vector3d(0.0f,8.0f,60.0f),Vector3d(-50.0f,0.0f,0.0f));
    Node* zaca = m.createMeshNode("assets/pruebi2.obj",false);
    Node* aranya = m.createMeshNode("assets/aranya/aranya.obj",false);
    Node* cabra = m.createMeshNode("assets/cabra/cabraa.obj",false);
    Node* criaa = m.createMeshNode("assets/cria/cria.obj",false);

    zaca->translate(Vector3d(-30,0,0));
    aranya->scale(Vector3d(-0.5f,-0.5f,-0.5f));
    cabra->scale(Vector3d(-0.8f,-0.8f,-0.8f));
    aranya->translate(Vector3d(0,0,0));
    cabra->translate(Vector3d(30,0,0));
    criaa->scale(Vector3d(-0.5,-0.5,-0.5));
    criaa->translate(Vector3d(-50,0,0));

    camera->setTarget(zaca);
    camera->setRotation(Vector3d(0,50,0));

    std::cout << "Target of camera:\n";
    std::cout << camera->getTarget().getVectorX() << " ";
    std::cout << camera->getTarget().getVectorY() << " ";
    std::cout << camera->getTarget().getVectorZ() <<"\n";
    



    m.beginScene();
    m.run();
    m.endScene();
    return 0;
}*/

/* PREVIO EN DEVELOPER */

/*#include <iostream>
#include "man/game.hpp"
#include "man/state.hpp"

struct MenuState_t : StateBase_t {
    explicit MenuState_t(StateManager_t& sm) : SM(sm) {}

    void update() final {
        std::cout << R"(
            MENU:
            1. Play
            2. Credits
            -. Exit
        )";

        int opt;

        std::cin >> opt;

        switch (opt) {
            case 1: SM.addState<GameManager_t>(SM); break;
            case 2: credits(); break;
            default: m_alive = false;
        }
    }

    bool alive() final {
        return m_alive;
    }

    void credits() {
        std::cout << R"(
            CREDITS:
            1. Paula Garcia Morales
            2. Laura Gil Lopez
            3. Jorge Perez Dominguez
            4. Alba Ruiz Maiques
            5. Javier Sibada Lopez
            6. Miguel Teruel Carvajal
            -. Exit
        )";
    }

    private:
        bool m_alive { true };
        StateManager_t& SM;
};

int main(){
    try {
        StateManager_t States;
        States.addState<MenuState_t>(States);

        while (States.alive()) {
            States.update();
        }    
    } catch (std::exception& e) {
        std::cout << "[[ EXCEPTION ]]: " << e.what() << "\n\n";
    } catch(...){
        std::cout << "Capturada : \n";
    }
}*/
