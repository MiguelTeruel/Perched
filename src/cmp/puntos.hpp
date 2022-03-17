#pragma once
#include "component.hpp"
#include <iostream>

struct PuntosComponent_t : public ECS::ComponentBase_t<PuntosComponent_t> {
    explicit PuntosComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    uint32_t puntos { 0 };
    uint32_t cantSumable { 10 };
};