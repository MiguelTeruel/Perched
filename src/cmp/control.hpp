#pragma once
#include "component.hpp"
#include "entity.hpp"
#include "../util/typealiases.hpp"
#include <iostream>

struct ControlComponent_t : public ECS::ComponentBase_t<ControlComponent_t> {
    explicit ControlComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {
        puntosControl.reserve(100);
    };

    ECS::Vec_t<ECS::EntityID_t> puntosControl {};
};