#include "systems/PlayerSys.h"

#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "core/Constants.h"
#include "core/Conversions.h"
#include "game/BlockInfo.h"

void PlayerSystem::Init(World& world, Camera2D& camera, entt::entity player)
{
    mWorldPtr = &world;
    mCameraPtr = &camera;
    mPlayer = player;
}

void PlayerSystem::Update(entt::registry& reg, float dt)
{
    auto& rb = reg.get<RigidBody>(mPlayer);
    auto& stats = reg.get<Stats>(mPlayer);

    ApplyMovement(rb, stats, dt);
    Interact(rb, stats, dt);
}

void PlayerSystem::ApplyMovement(RigidBody& rb, Stats& stats, float dt)
{
    Vector2 direction(0.0f, 0.0f);

    if (IsKeyDown(KEY_A)) direction.x -= 1; // Move left
    if (IsKeyDown(KEY_D)) direction.x += 1; // Move right
    if (IsKeyDown(KEY_W)) direction.y -= 1; // Move up
    if (IsKeyDown(KEY_S)) direction.y += 1; // Move down

    bool sprinting = false;
    if (IsKeyDown(KEY_LEFT_SHIFT)) sprinting = true;

    // Return if not moved
    if (direction.x == 0 && direction.y == 0) return;
    // Normalize direction vector
    direction = Vector2Normalize(direction);

    // Set the correct speed
    float speed = !sprinting ? stats.speed : stats.speed * stats.sprintMul;

    // Apply horizontal movement
    rb.velX = direction.x * speed * dt;

    // Only apply vertical movement if the player has no gravity so he can fly.
    if (!rb.hasGravity) { rb.velY = direction.y * speed * dt; }
}

void PlayerSystem::Interact(RigidBody& rb, Stats& stats, float dt)
{
    if (mLastInteraction < 0.1f) {
        mLastInteraction += dt;
        return;
    }

    if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) return;
    auto clickPos = GetScreenToWorld2D(GetMousePosition(), *mCameraPtr);

    Vector2 rayOrigin = rb.GetCenter();
    Vector2 rayDirection = clickPos - rayOrigin;
    rayDirection = Vector2Normalize(rayDirection);

    float rayDistance = 0.0f;

    while (rayDistance <= stats.reach) {
        rayOrigin.x += rayDirection.x * BLOCK_SIZE_PIXELS;
        rayOrigin.y += rayDirection.y * BLOCK_SIZE_PIXELS;
        rayDistance += 1.0f;

        int chunkIndex = ChunkPositionToIndex(WorldToChunkPosition(rayOrigin));
        int blockIndex = WorldToBlockIndex(rayOrigin);
        Chunk& currChunk = mWorldPtr->GetChunk(chunkIndex);
        Block& currBlock = currChunk.BlockAt(blockIndex);

        if (BLOCK_INFO[currBlock.id].isSolid) {
            currChunk.MineBlock(blockIndex, 0.1f);
            mWorldPtr->SetForceChunkUpdate(chunkIndex);
            break;
        }
    }
    mLastInteraction = 0.0f;
}

void PlayerSystem::RenderDbg(entt::registry& reg) const
{
    auto& rb = reg.get<RigidBody>(mPlayer);
    auto rbCenter = rb.GetCenter();
    auto& stats = reg.get<Stats>(mPlayer);
    auto mousePos = GetMousePosition();

    // Convert mouse position to world coordinates
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePos, *mCameraPtr);

    // Calculate the end point of the line based on the player's reach
    float reachInPixels = stats.reach * BLOCK_SIZE_PIXELS;
    Vector2 lineEndPos = rb.GetCenter() + Vector2Normalize(mouseWorldPos - rbCenter) * reachInPixels;

    // Draw the line
    DrawLineEx(rbCenter, lineEndPos, 2.0f, PURPLE);
}