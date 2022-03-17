#pragma once
#include "component.hpp"
#include "../Motor3D/Node.hpp"

struct FollowComponent_t : public ECS::ComponentBase_t<FollowComponent_t> {
    explicit FollowComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    float x { 0 }, y { 0 }, z { 0 };
    ECS::EntityID_t followEntityID { 0 };
};