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
//# Entity almacena los componentes asociados a la entidad creada,   #
//#   para ello tiene funciones de obtener componentes y anyadirlos. #
//#                                                                  #
//#                                                                  #
//####################################################################

 #pragma once
 #include <cstdint>
 #include <unordered_map>
 #include "physics.hpp"
 #include "render.hpp"
 #include "input.hpp"
 #include "../util/typealiases.hpp"
 

 namespace ECS{ 
    struct Entity_t{
        explicit Entity_t () = default;

        //constexpr es para que se haga en tiempo de compilacion
        constexpr EntityID_t getEntityID() const noexcept { return entityID; }
        

        //me pasan un tipo de componente, busco el id del tipo de componente
        //y pongo en mi vector de componentes, el componente pasado
        template <typename CMP_t>
        void addComponent(CMP_t& c) {
            auto type = CMP_t::getComponentTypeID();
            componentes[type] = &c;
        }

        template <typename CMP_t>
        void addComponentVisual(CMP_t& c) {
            auto type = CMP_t::getComponentTypeID();
            visualCollider[type] = &c;
        }


        //obtengo el id del tipo de componente, lo busco en mi vector de componentes
        //y devuelvo el componente correspondiente al tipo
        template <typename CMP_t>
        CMP_t* getComponent() {
            auto type = CMP_t::getComponentTypeID();
            auto it = componentes.find(type);

            if ( it != componentes.end() ) {
                return static_cast<CMP_t*>(it->second);
            }

            return nullptr;
        }

        template <typename CMP_t>
        CMP_t* getComponentVisual() {
            auto type = CMP_t::getComponentTypeID();
            auto it = visualCollider.find(type);

            if ( it != componentes.end() ) {
                return static_cast<CMP_t*>(it->second);
            }

            return nullptr;
        }

        template <typename CMP_t>
        const CMP_t* getComponent() const {
            auto p = const_cast<Entity_t*>(this)->getComponent<CMP_t>();
            
            return const_cast<const CMP_t*>(p);
        }


        //si encuentro el tipo de componente correspondiente a la entidad, actualizo su puntero
        void updateComponent(ComponentTypeID_t cid, Component_t* cmpptr) {
            auto it = componentes.find(cid);

            if ( it != componentes.end() ) {
                it->second = cmpptr;
            }
        }

        auto begin() { return componentes.begin(); }
        auto end() { return componentes.end(); }

        private:
            Hash_t<ComponentTypeID_t, Component_t*> componentes;

            EntityID_t entityID { ++nextID };

            inline static EntityID_t nextID { 0 };

            //Componente Collider visual
            Hash_t<ComponentTypeID_t, Component_t*> visualCollider;
    };
 }