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

#include "entitymanager.hpp"

namespace ECS{

    EntityManager_t::EntityManager_t(){
        m_Entity.reserve(InitialEntities);
    }


    //obtengo la entidad a partir del id, recorro los componentes de la entidad
    //llamo a deleteComponent y me devuelve un componente que hay que actualizar
    //obtengo la entidad del componente movido y actualizo su puntero a componente
    //por ultimo, cojo la entidad y la borro
    void EntityManager_t::destroyEntityByID(EntityID_t eid) {
        auto* entity { getEntityByID(eid) };

        if (!entity) { return; }

        for (auto& [typeID, cmp] : *entity) {
            //borrar componentes
            auto* cmpptr = m_components.deleteComponentByTypeIDAndEntityID(typeID, eid);

            if (!cmpptr) { return; }

            auto* movedEntity { getEntityByID(cmpptr->getEntityID()) };

            movedEntity->updateComponent(typeID, cmpptr);
        }

        auto it = std::find_if(m_Entity.begin(), m_Entity.end(), 
            [&](const Entity_t& e){ return e.getEntityID() == eid;}
        );

        m_Entity.erase(it);
    }

    const Entity_t* EntityManager_t::getEntityByID(EntityID_t eid) const {
        auto it = std::find_if(m_Entity.begin(), m_Entity.end(), 
            [&](const Entity_t& e){ return e.getEntityID() == eid;}
        );

        if (it == m_Entity.end()) {
            return nullptr;
        }

        return it.base();
    }

    Entity_t* EntityManager_t::getEntityByID(EntityID_t eid) {
        //const_cast hace el objeto constante para poder pasarselo al metodo de arriba
        //luego se vuelve a hacer const_cast para que el objeto devuelto no sea const
        
        auto eptr = const_cast<const EntityManager_t*>(this)->getEntityByID(eid);

        return const_cast<Entity_t*>(eptr);
    }
}