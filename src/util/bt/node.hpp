#pragma once
#include <cstdint>
#include "../stbe/Steering.hpp"
#include "../../cmp/ia.hpp"
#include "../../cmp/entity.hpp"
#include "../../cmp/physics.hpp"

#include "../../cmp/blackboard.hpp"


struct EntityContext_t{
    ECS::Entity_t           *enty;
    IAComponent_t           *ia;
    PhysicsComponent_t      *phy;
    BlackboardComponent_t   *bb;
};

enum class IA_Stats {
    Energia,
    Ira,
    Cansancio
};

enum class BTNodeStatus_t : uint8_t{
    success,
    fail,
    running
};

struct BTNode_t{
    struct Deleter { void operator()(BTNode_t* n){ n->~BTNode_t(); } };
    BTNode_t()                           = default;
    BTNode_t(const BTNode_t&)            = delete;
    BTNode_t( BTNode_t&)                 = delete;
    BTNode_t& operator=(const BTNode_t&) = delete;
    BTNode_t& operator=( BTNode_t&&)     = delete;



    virtual BTNodeStatus_t run(EntityContext_t &ectx) noexcept = 0;

    virtual ~BTNode_t() = default;
};