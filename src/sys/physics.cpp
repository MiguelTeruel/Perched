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

#include "physics.hpp"

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::physicsRoca(GameCTX_t& g, PhysicsComponent_t& phy, ColliderComponent_t& col) const {
    for(auto& phy1: g.template getComponents<PhysicsComponent_t>()){
        auto* col1 = g.template getRequiredComponent<PhysicsComponent_t, ColliderComponent_t>(phy1);
        
        if (col1 != nullptr && col1->properties == ColliderComponent_t::P_IsPlayer) {
            float dist = sqrt(pow(phy.x - phy1.x, 2) + pow(phy.y - phy1.y, 2)); 

            /*crea una linea a la entidad con componente damages*/
            auto* rc = g.template getRequiredComponent<PhysicsComponent_t, RenderComponent_t>(phy);
            //rc->entityNodes.ray = true;
            //rc->entityNodes.x = rc->entityNodes.node.node->getX();
            //rc->entityNodes.y = rc->entityNodes.node.node->getY();
            //rc->entityNodes.z = 15;
            //rc->entityNodes.rot = asin((phy.x+phy1.x)/dist)*180/PI;

            if (dist <= 250) {
                if (col.nomover == true) {
                    phy.rotx += 20;

                    //gravedad
                    phy.vy -= phy.gravity;
                    phy.vy = std::clamp(phy.vy, phy.KminVy, phy.KmaxVy); //mantener valor en rango
                }
            } 
        }
    }
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::physicsIA(GameCTX_t& g, PhysicsComponent_t& phy) const {
    auto* ia = g.template getRequiredComponent<PhysicsComponent_t, IAComponent_t>(phy);

    if (ia != nullptr && ia->estadoIA == BTState::change_target_init) {
        //std::cout << "Inicio: " << phy.x << " " << phy.y << " Fin: " << ia->tx << " " << ia->ty << "\n";
        //std::cout << "InicioC: " << phy.x/20 << " " << phy.y/20 << " FinC: " << ia->tx/20 << " " << ia->ty/20 << "\n";

        Casilla ini;
        ini.x = phy.x / 20;
        ini.y = phy.y / 20;

        Casilla fin;
        fin.x = ia->tx / 20;
        fin.y = ia->ty / 20;

        if (std::abs(ini.x - fin.x) > 1 || std::abs(ini.y - fin.y) > 1) {
            PathP_t PathP{75, 45};

            PathP.ponerSalientes(75, 45, g.template getBlackBoard().salientes_bb);

            std::vector<Casilla> ruta = PathP.buscar(ini.x, ini.y, fin.x, fin.y);

            if (ruta.size() > 0)
            {
                //std::cout << "encontrado\n";
                ruta.push_back(fin);

                ia->pathplaneo = true;
                ia->ruta = ruta;
            }
        }
    }

    phy.orientation += phy.v_angular;
    if (phy.orientation > 2*PI) phy.orientation -= 2*PI;
    if (phy.orientation < 0) phy.orientation += 2*PI;

    phy.vx = phy.v_linear * std::cos(phy.orientation);
    phy.vy = phy.v_linear * std::sin(phy.orientation);
}

template <typename GameCTX_t>
bool PhysicsSystem_t<GameCTX_t>::update(GameCTX_t& g) {
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){
        auto* col = g.template getRequiredComponent<PhysicsComponent_t, ColliderComponent_t>(phy);

        //rocas
        if (col != nullptr && col->properties == ColliderComponent_t::P_Damages) {
            physicsRoca(g, phy, *col);
        }

        if (col != nullptr && col->properties == ColliderComponent_t::P_Enemy) {
            physicsIA(g, phy);
        }

        
        //aceleracion
        //phy.vx += phy.ax;
        //phy.vx = std::clamp(phy.vx, phy.KminVx, phy.KmaxVx);

        //actualizar posiciones
        phy.last_x = phy.x;
        phy.last_y = phy.y;
        
        phy.x += phy.vx;
        phy.y += phy.vy;
    }

    return true;
}      


template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::comprobarTunel(int quesubirbajar, GameCTX_t& g){
    if (tunel == 1){
        if(cambioplano==0){
            entrarTunel(quesubirbajar, g);
            cambioplano=1;
        }else if(cambioplano==1){
            salirTunel(quesubirbajar, g);
            cambioplano=0;
        }            
        contTunel++;
    } else {
        contTunel = 0;
    }        
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::resetTunel(GameCTX_t& g) noexcept {
    tunel = 0;
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::addTunel(GameCTX_t& g) noexcept {
    tunel++;
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::calculozinicio(GameCTX_t& g){
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){
        phy.zinicial = phy.z;
    }
}

template <typename GameCTX_t>
bool PhysicsSystem_t<GameCTX_t>::entrarTunel(int quesubirbajar, GameCTX_t& g) const{
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){

        auto* col = g.template getRequiredComponent<PhysicsComponent_t,ColliderComponent_t>(phy);

        if(col!=nullptr){
            if ((col->subirbajar == quesubirbajar) || (col->quesubirbajar == quesubirbajar)) {
                if (!((col->properties == ColliderComponent_t::P_Agujero) || (col->properties == ColliderComponent_t::P_Trampolin))) {
                    if(col->properties == ColliderComponent_t::P_PlanoS){
                        phy.z= -10;
                    }

                    if(col->properties == ColliderComponent_t::P_Saliente){
                        phy.z= 60;            
                    }

                    if (col->properties == ColliderComponent_t::P_Semilla) {
                        phy.z = 10;
                    }

                    if ((col->properties == ColliderComponent_t::P_Control) || (col->properties == ColliderComponent_t::P_Arbusto)
                        || (col->properties == ColliderComponent_t::P_Nido) || (col->properties == ColliderComponent_t::P_Cria)) {
                        phy.z = 20;
                    }
                }
            } else {
                if (!(col->properties == ColliderComponent_t::P_IsPlayer)) {
                    phy.z += 250;
                }                
            }
        }
    }
    return true;
}

template <typename GameCTX_t>
bool PhysicsSystem_t<GameCTX_t>::salirTunel(int quesubirbajar, GameCTX_t& g) const{
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){

        auto* col = g.template getRequiredComponent<PhysicsComponent_t,ColliderComponent_t>(phy);

        if(col!=nullptr){
            if (col->subirbajar == quesubirbajar) {
                if (!((col->properties == ColliderComponent_t::P_Agujero) || (col->properties == ColliderComponent_t::P_Trampolin))) {
                    phy.z= 400;
                }
            } else {
                phy.z = phy.zinicial;
            }
        }
    }
    return true;
}