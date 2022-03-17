#pragma once
#include "component.hpp"
#include <iostream>

struct StaminaComponent_t : public ECS::ComponentBase_t<StaminaComponent_t> {
    explicit StaminaComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    uint32_t maxStamina { 0 };
    uint32_t cantStamina { 0 };
};