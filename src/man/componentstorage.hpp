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
//# ComponentStorage sirve para guardar y gestionar los vectores     #
//#   de componentes que se van creando segun el tipo de componente  #
//#   en un unordenered_map.                                         #
//#                                                                  #
//####################################################################

#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <optional>
#include "../cmp/physics.hpp"
#include "../cmp/ia.hpp" 
#include "../cmp/render.hpp"
#include "../cmp/input.hpp"
#include "../util/typealiases.hpp"

namespace ECS{

    struct ComponentVectorBase_t {
        virtual ~ComponentVectorBase_t() = default;
        virtual Component_t* deleteComponentByEntityID(EntityID_t eid) = 0;
    };

    template <typename CMP_t>
    struct ComponentVector_t : ComponentVectorBase_t {
        Vec_t<CMP_t> components;


        //si encuentra el componente, devuelve su iterador, sino devuelve 0
        constexpr auto findComponentIteratorById(EntityID_t eid) noexcept {
            std::optional itopt = std::find_if(components.begin(), components.end(),
                [&eid](auto& cmp) {
                    return cmp.getEntityID() == eid;
                }
            );

            if (*itopt == components.end()) { itopt.reset(); }

            return itopt;
        }


        //busco el componente correspondiente a la entidad
        //si lo encuentro y no es el ultimo, copio el ultimo en mi posicion
        //saco el ultimo componente del vector y devuelvo el componente copiado
        Component_t* deleteComponentByEntityID(EntityID_t eid) override final {
            auto itopt = findComponentIteratorById(eid);

            if (!itopt) { return nullptr; }

            auto it = *itopt;

            if (it + 1 != components.end()) {
                *it = components.back();
            }

            components.pop_back();

            return it.base();
        }
    };
 
    struct ComponentStorage_t{
        explicit ComponentStorage_t(std::size_t initialsize) : m_initialSize(initialsize){
        };

        //no hacer copias ni asignaciones de objetos ComponentStorage_t
        ComponentStorage_t(const ComponentStorage_t&) = delete;
        ComponentStorage_t(ComponentStorage_t&&) = delete;
        ComponentStorage_t& operator=(const ComponentStorage_t&) = delete;
        ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;


        //obtener el vector de componentes que quiero, y almacenar 
        //el id de la entidad para obtener el componente
        template <typename CMP_t>
        CMP_t& createComponent(EntityID_t eid) {            
            auto& v = getComponents<CMP_t>();

            auto& cmp = v.emplace_back(eid);
            
            return cmp;
        }


        //creo un vector del componente pasado, reservo espacio para sus elementos,
        //obtengo el id del tipo de componente y muevo el vector al almacen
        template <typename CMP_t>
        Vec_t<CMP_t>& createComponentVector() {
            auto v = std::make_unique<ComponentVector_t<CMP_t>>();
            v->components.reserve(m_initialSize);

            auto* vecptr = v.get();

            auto typeID = CMP_t::getComponentTypeID();
            m_componentVector[typeID] = std::move(v);

            return vecptr->components;
        }


        //obtengo el tipo de componente pasado, si encuentro el vector del tipo de componente en el 
        //almacen lo devuelvo, si no creo un vector para el tipo de componente pasado
        template <typename CMP_t>
        Vec_t<CMP_t>& getComponents() {
            Vec_t<CMP_t>* comvec { nullptr };

            auto typeID = CMP_t::getComponentTypeID();

            auto it = m_componentVector.find(typeID);

            if ( it != m_componentVector.end() ) {
                //dynamic_cast se pone cuando las clases son polimorficas en vez de static_cast
                auto* v = dynamic_cast<ComponentVector_t<CMP_t>*>(it->second.get());

                if (v != nullptr) {
                    comvec = &(v->components);
                }                
            } else {
                comvec = &createComponentVector<CMP_t>();
            }

            return *comvec;
        }


        //si es const, hace lo mismo que arriba, pero si no encuentra el vector no lo crea
        template <typename CMP_t>
        const Vec_t<CMP_t>& getComponents() const {
            Vec_t<CMP_t>* comvec { nullptr };

            auto typeID = CMP_t::getComponentTypeID();

            auto it = m_componentVector.find(typeID);

            if ( it != m_componentVector.end() ) {
                //dynamic_cast se pone cuando las clases son polimorficas en vez de static_cast
                auto* v = dynamic_cast<ComponentVector_t<CMP_t>*>(it->second.get());

                if (v != nullptr) {
                    comvec = &(v->components);
                } 
            } else {
                //comvec = &CMP_t::createComponentVector();

                throw "Asi no, payaso!";
            }

            return *comvec;
        }


        //busco el vector de componentes del tipo que me pasan, si no lo encuentro devuelvo nullptr
        //si lo encuentro, llamo a delete y me devuelven el componente que hay que actualizar
        Component_t* deleteComponentByTypeIDAndEntityID(ComponentTypeID_t cid, EntityID_t eid) {
            auto it = m_componentVector.find(cid);

            if (it == m_componentVector.end()) { return nullptr; }

            return it->second.get()->deleteComponentByEntityID(eid);
        }


        private:
            Hash_t<ComponentTypeID_t, UPtr<ComponentVectorBase_t>> m_componentVector;

            std::size_t m_initialSize { 100 };
    };

}