#pragma once
#include <iostream>
#include "node.hpp"

struct BT_Change_Target_From_Init : BTNode_t{
    BT_Change_Target_From_Init (double x, double y) : new_x{x} , new_y{y}{}

    //Cambia el XT y el YT de la IA por una posicion con referencia a la posicion de inicio
    //Se usa para que la IA por ahora se mueva

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::change_target_init;

        ectx.ia->tx = ectx.ia->ix + new_x;
        ectx.ia->ty = ectx.ia->iy + new_y;
        return BTNodeStatus_t::success;
    }

    private:
        double new_x {0.0};
        double new_y {0.0};

};