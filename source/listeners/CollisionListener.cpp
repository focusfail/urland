#include "listeners/CollisionListener.h"

#include "components/RigidBody.h"

#include <iostream>

void CollisionListener::HandleCollision(entt::registry& reg, entt::entity entity)
{
    auto& rb = reg.get<RigidBody>(entity);

    if (rb.dx == 0.0f && rb.dy == 0.0f) return;

    // Handle horizontal movement
    if (rb.dx != 0.0f) { // only check if moved horizontally
        RigidBody horizontal_rb = rb;
        horizontal_rb.x += rb.dx;
        RigidBody collision_rb;
        if (CheckCollision(horizontal_rb, collision_rb)) {
            if (rb.dx > 0) { rb.x = collision_rb.x - rb.width; }
            else {
                rb.x = collision_rb.x + collision_rb.width;
            }
            rb.dx = 0.0f;
        }
        else {
            rb.x += rb.dx;
        }
    }

    // Handle vertical movement
    if (rb.dy != 0.0f) { // only check if moved vertically
        RigidBody vertical_rb = rb;
        vertical_rb.y += rb.dy;
        RigidBody collision_rb;
        if (CheckCollision(vertical_rb, collision_rb)) {
            if (rb.dy > 0) { rb.y = collision_rb.y - rb.height; }
            else {
                rb.y = collision_rb.y + collision_rb.height;
            }
            rb.dy = 0.0f;
        }
        else {
            rb.y += rb.dy;
        }
    }

    // Reset the delta positions
    rb.dx = 0.0f;
    rb.dy = 0.0f;
}

bool CollisionListener::CheckCollision(const RigidBody& entity_rb, RigidBody& out_collision_rb)
{
    int start_chunk_x = static_cast<int>(entity_rb.x / CHUNK_PIXEL_SIZE);
    int end_chunk_x = static_cast<int>((entity_rb.x + entity_rb.width) / CHUNK_PIXEL_SIZE);
    int start_chunk_y = static_cast<int>(entity_rb.y / CHUNK_PIXEL_SIZE);
    int end_chunk_y = static_cast<int>((entity_rb.y + entity_rb.height) / CHUNK_PIXEL_SIZE);

    for (int chunk_y = start_chunk_y; chunk_y <= end_chunk_y; ++chunk_y) {
        for (int chunk_x = start_chunk_x; chunk_x <= end_chunk_x; ++chunk_x) {
            int chunk_index = chunk_y * WORLD_WIDTH + chunk_x;
            if (chunk_index >= 0 && chunk_index < CHUNK_LENGTH) {
                const Chunk& chunk = m_world->GetChunkArray()->at(chunk_index);
                const auto& bounding_boxes = chunk.GetBoundingBoxes();

                for (const auto& bb : bounding_boxes) {
                    RigidBody global_rb(bb.x + chunk_x * CHUNK_PIXEL_SIZE, bb.y + chunk_y * CHUNK_PIXEL_SIZE, bb.width,
                                        bb.height);

                    if (entity_rb.Intersects(global_rb)) {
                        out_collision_rb = global_rb;
                        return true; // Collision detected
                    }
                }
            }
        }
    }

    return false; // No collision
}