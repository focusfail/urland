#ifndef PLAYER_SYS
#define PLAYER_SYS
#include "entt/entt.hpp"

#include "components/PlayerTag.h"
#include "components/Stats.h"
#include "components/RigidBody.h"
#include "game/world/World.h"

class PlayerSystem
{
public:
    PlayerSystem() = default;
    ~PlayerSystem() = default;
    void Init(World& world, Camera2D& camera, entt::entity player);

    void Update(entt::registry& reg, float dt);
    void ApplyMovement(RigidBody& rb, Stats& stats, float dt);
    void Interact(RigidBody& rb, Stats& stats, float dt);
    void RenderDbg(entt::registry& reg) const;

private:
    entt::entity mPlayer;
    World* mWorldPtr;
    Camera2D* mCameraPtr;
    float mLastInteraction = 0.0f;
};

#endif // PLAYER_SYS