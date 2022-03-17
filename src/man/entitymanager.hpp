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
//# EntityManager sirve para guardar y gestionar las entidades que   #
//#   se van creando y destruyendo.                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <cassert>
#include <concepts>
#include <tuple>

#include "componentstorage.hpp"
#include "../util/typealiases.hpp"
#include "../util/gamecontext.hpp"
#include "../cmp/entity.hpp"
#include "../cmp/blackboard.hpp"
#include "../cmp/ia.hpp"

#include "../util/bt/node.hpp"
#include "../util/bt/ACTarrive.hpp"
#include "../util/bt/nodesequence.hpp"
#include "../util/bt/nodeselector.hpp"
#include "../util/bt/checktype.hpp"
#include "../util/bt/behaviourtree.hpp"




namespace ECS {
   
    struct EntityManager_t : public GameContext_t{   //entitymanager hereda de gamecontext
        static constexpr std::size_t InitialEntities { 300 };

        explicit EntityManager_t();

        Entity_t& createEntity() {
            return m_Entity.emplace_back();
        }   

        void destroyEntityByID(EntityID_t eid);     


        //obtengo el componente del tipo que quiero, si no esta creado, lo creo
        template <typename CMP_t>
        CMP_t& addComponent(Entity_t& e) {
            CMP_t* cmp_ptr { e.getComponent<CMP_t>() };

            if ( !cmp_ptr ) {
                auto& cmp = m_components.createComponent<CMP_t>(e.getEntityID());
                e.addComponent(cmp);
                cmp_ptr = &cmp;
            } 

            return *cmp_ptr;
        }

        template <typename CMP_t>
        CMP_t& addComponentVisual(Entity_t& e) {
            CMP_t* cmp_ptr { e.getComponent<CMP_t>() };

            auto& cmp = m_components.createComponent<CMP_t>(e.getEntityID());
            e.addComponentVisual(cmp);
            cmp_ptr = &cmp;

            return *cmp_ptr;
        }

        template <typename CMP_t>
        Entity_t* getEntityPointerFromComponent(const CMP_t& cmp) {
            return getEntityByID( cmp.getEntityID() );
        }

        template <typename CMP_t>
        const Entity_t* getEntityPointerFromComponent(const CMP_t& cmp) const {
            return getEntityByID( cmp.getEntityID() );
        }

        template <typename CMP_t, typename ReqCMP_t>
        const ReqCMP_t* getRequiredComponent(const CMP_t& cmp) const {
            auto* e = getEntityPointerFromComponent(cmp);

            if (e) {
                return e->template getComponent<ReqCMP_t>();
            }

            return nullptr;
        }

        template <typename CMP_t, typename ReqCMP_t>
        ReqCMP_t* getRequiredComponent(const CMP_t& cmp) {
            const auto* rc = const_cast<const EntityManager_t*>(this)->getRequiredComponent<CMP_t, ReqCMP_t>(cmp);

            return const_cast<ReqCMP_t*>(rc);
        }

        const Entity_t* getEntityByID(EntityID_t eid) const;
        Entity_t* getEntityByID(EntityID_t eid);
        
        const Vec_t<Entity_t>& getEntities() const { return m_Entity; } 
        Vec_t<Entity_t>& getEntities() { return m_Entity; }
        

        template <typename CMP_t>
        const Vec_t<CMP_t>& getComponents() const { return m_components.getComponents<CMP_t>(); }

        template <typename CMP_t>
        Vec_t<CMP_t>& getComponents() { return m_components.getComponents<CMP_t>();}

        auto& getBlackBoard() { return m_blackBoard; }

        ComponentStorage_t& getStorageComponents(){
            return m_components;
        }

        private:
            Vec_t<Entity_t> m_Entity {};
            ComponentStorage_t m_components {InitialEntities};

            BlackboardComponent_t m_blackBoard {};
    };

}

