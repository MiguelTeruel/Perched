#include "follow.hpp"
#include "../cmp/follow.hpp"
#include "../cmp/physics.hpp"

template <typename GameCTX_t>
constexpr void FollowSystem_t<GameCTX_t>::update(GameCTX_t& g) const noexcept {
    for(auto& fol: g.template getComponents<FollowComponent_t>()){
        auto* entity { g.getEntityByID(fol.followEntityID) };
        if (!entity) { continue; }

        auto* entPhy { entity->template getComponent<PhysicsComponent_t>() };
        if (!entPhy) { continue; }

        auto* phy { g.template getRequiredComponent<FollowComponent_t, PhysicsComponent_t>(fol) };
        if (!phy) { continue; }

        phy->x = entPhy->x + fol.x;
        phy->y = entPhy->y + fol.y;
        phy->z = entPhy->z + fol.z;
    }
} 