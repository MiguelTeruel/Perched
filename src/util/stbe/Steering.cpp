#include "Steering.hpp"
#include "../../cmp/physics.hpp"
#include <iostream>

#include <cmath>
#include <cstdint>
#include <stdio.h>
#include <iomanip>
#include <algorithm>


namespace STBEH{

    Steer_t arrive(PhysicsComponent_t * phy, Point2D_t * target, double & time2arrive, double & arrivalRadius){

        Steer_t salida;

        auto vtx { target->x - phy->x };
        auto vty { target->y - phy->y };

        auto vtlin { std::sqrt(vtx*vtx + vty*vty) };
        if (vtlin < arrivalRadius){
        //    tactive = false;
            return salida;
        }
        salida.linear = std::clamp( vtlin / time2arrive, -phy->KmaxVLin, phy->KmaxVLin );


        auto torient{ std::atan2(vty, vtx) };
        if ( torient < 0 ) torient += 2*PI;
        auto vang { torient - phy->orientation };
        if ( vang > PI ) vang -= 2*PI;
        else if ( vang < -PI ) vang += 2*PI;
        salida.angular = std::clamp( vang / time2arrive, -phy->KmaxVang, phy->KmaxVang );
        return salida;
    }


    Steer_t seek(PhysicsComponent_t * phy, Point2D_t * target, double & time2arrive, double & arrivalRadius){

        Steer_t salida;

        auto vtx { target->x - phy->x };
        auto vty { target->y - phy->y };

        auto vtlin { std::sqrt(vtx*vtx + vty*vty) };


        
        auto torient{ std::atan2(vty, vtx) };
        if ( torient < 0 ) torient += 2*PI;


        auto angular_distance { torient - phy->orientation };
        if ( angular_distance > PI ) angular_distance -= 2*PI;
        else if ( angular_distance < -PI ) angular_distance += 2*PI;
        auto angular_velocity { angular_distance / time2arrive };
        salida.angular = std::clamp( angular_velocity, -phy->KmaxVang, phy->KmaxVang );

        salida.linear = (phy->KmaxVLin / (1 + std::fabs(angular_velocity)));
        


        return salida;
    }

    Steer_t seek_one(PhysicsComponent_t * phy, Point2D_t * target, double & time2arrive, double arrivalRadius){

        Steer_t salida;

        auto vtx { target->x - phy->x };
        auto vty { target->y - phy->y };
        auto vtlin { std::sqrt(vtx*vtx + vty*vty) };
        
        auto torient{ std::atan2(0, vtx) };

        if ( torient < 0 ) torient += 2*PI;


        auto angular_distance { torient - phy->orientation };
        if ( angular_distance > 2*PI ) angular_distance -= 2*PI;
        else if ( angular_distance < 0 ) angular_distance += 2*PI;
        auto angular_velocity { angular_distance/ time2arrive };
        salida.angular = angular_velocity;

        //salida.linear = (phy->KmaxVLin / (1 + std::fabs(angular_velocity)));
        salida.linear = std::clamp( vtlin, -phy->KmaxVLin, phy->KmaxVLin );
        


        return salida;
    }


};