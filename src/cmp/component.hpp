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
//# Component es la clase de donde heredan todos los componentes,    #
//#   aqui se almacena el id del componente y la entidad asociada    #
//#   al componente.                                                 #
//#                                                                  #
//####################################################################

#pragma once
#include <cstdint>
#include "../util/typealiases.hpp"

namespace ECS {
    struct Component_t {
        explicit Component_t(EntityID_t eid) : entityID{ eid }
        {}    

        constexpr EntityID_t getEntityID() const noexcept { return entityID; }       

        private:
            ComponentID_t componentID { ++nextID };
            inline static ComponentID_t nextID { 0 };
            EntityID_t entityID { 0 };

        protected:
            //inline es para hacer definicion y declaracion a la vez
            inline static ComponentTypeID_t nextTypeID { 0 };
    };

    template <typename TYPE>
    struct ComponentBase_t : Component_t {
        explicit ComponentBase_t(EntityID_t eid) : Component_t{ eid }
        {} 

        //la variable typeID es especifica para cada tipo de componente
        //si no esta inicializada para el tipo de componente pasado, se inicializa con ++nextTypeID
        static ComponentTypeID_t getComponentTypeID() noexcept { 
            static ComponentTypeID_t typeID { ++nextTypeID };
            return typeID;
        }
    };
}