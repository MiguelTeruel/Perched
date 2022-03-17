#pragma once
#include <iostream>
#include "node.hpp"

struct BT_ACT_arrive_t : BTNode_t{
    BT_ACT_arrive_t (){}

    //Comprueba si la IA ha llegado a la coord que se le ha pasado

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::ACTarrive;

        if (ectx.ia->pathplaneo) {
//            if (ectx.ia->enemy == type_enemy::Aguila) {
//                std::cout << "pathplanneo\n";
//            }
            
            //std::cout << "Indice: " << ectx.ia->indiceRuta << " Size: " << ectx.ia->ruta.size() << "\n";

            if (ectx.ia->indiceRuta < ectx.ia->ruta.size()) {
                Point2D_t target{ectx.ia->ruta.at(ectx.ia->indiceRuta).x * 20.0, ectx.ia->ruta.at(ectx.ia->indiceRuta).y * 20.0};

                //cuando es la ultima casilla de la ruta compuebo si he llegado
                if (ectx.ia->indiceRuta == ectx.ia->ruta.size()-1) {
                    STBEH::Steer_t st = STBEH::arrive( ectx.phy, &target, ectx.ia->time2arrivePath, ectx.ia->arrivalRadius);

                    ectx.phy->v_linear= st.linear;
                    ectx.phy->v_angular= st.angular;

                    if(st==STBEH::Steer_t{}){
                        return BTNodeStatus_t::success;
                    }
                } else {
                    STBEH::Steer_t st1 = STBEH::arrive( ectx.phy, &target, ectx.ia->time2arrivePath, ectx.ia->arrivalRadius);

                    ectx.phy->v_linear= st1.linear;
                    ectx.phy->v_angular= st1.angular;
                }

                ectx.ia->indiceRuta++;
            } else {
                ectx.ia->pathplaneo = false;
                ectx.ia->indiceRuta = 0;
            }
        } else {
//            if (ectx.ia->enemy == type_enemy::Aguila) {
//                std::cout << "no pathplanneo\n";
//            }

            Point2D_t target{ectx.ia->tx, ectx.ia->ty};
            STBEH::Steer_t st = STBEH::arrive( ectx.phy, &target, ectx.ia->time2arrive, ectx.ia->arrivalRadius);

            ectx.phy->v_linear= st.linear;
            ectx.phy->v_angular= st.angular;

            if(st==STBEH::Steer_t{}){
                return BTNodeStatus_t::success;
            }
        }

        //Point2D_t target{ectx.ia->tx, ectx.ia->ty};
        //st = STBEH::arrive( ectx.phy, &target, ectx.ia->time2arrive, ectx.ia->arrivalRadius);

        return BTNodeStatus_t::running;
    }

    private:
        
};