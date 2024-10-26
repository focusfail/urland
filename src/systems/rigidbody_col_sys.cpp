#include "systems/rigidbody_col_sys.h"
#include "core/conversions.h"
#include "core/constants.h"

void RigidBodyCollisionSystem::Init(World& world) { mWorld = &world; }

void RigidBodyCollisionSystem::Update(entt::registry& reg)
{
    auto view = reg.view<RigidBody>();

    for (auto entity : view) {
        RigidBody& rb = view.get<RigidBody>(entity);
        if (rb.velX == 0.0f && rb.velY == 0) continue;

        if (!rb.collides) {
            rb.x += rb.velX;
            rb.y += rb.velY;

            rb.velX = 0;
            rb.velY = 0;
        }

        // Handle horizontal movement
        if (rb.velX != 0.0f) { // only check if moved horizontally
            RigidBody horRb = rb;
            horRb.x += rb.velX;
            RigidBody colRb;
            if (mCheckCollision(horRb, colRb)) {
                if (rb.velX > 0) { rb.x = colRb.x - rb.width; }
                else {
                    rb.x = colRb.x + colRb.width;
                }
                rb.velX = 0.0f;
            }
            else {
                rb.x += rb.velX;
            }
        }

        // Handle vertical movement
        if (rb.velY != 0.0f) { // only check if moved vertically
            RigidBody verRb = rb;
            verRb.y += rb.velY;
            RigidBody colRb;
            if (mCheckCollision(verRb, colRb)) {
                if (rb.velY > 0) { rb.y = colRb.y - rb.height; }
                else {
                    rb.y = colRb.y + colRb.height;
                }
                rb.velY = 0.0f;
            }
            else {
                rb.y += rb.velY;
            }
        }

        // Reset the delta positions
        rb.velX = 0.0f;
        rb.velY = 0.0f;
    }
}

bool RigidBodyCollisionSystem::mCheckCollision(const RigidBody& rb, RigidBody& out_rb)
{
    auto [startChunkX, startChunkY] = WorldToChunkPosition(Vector2 {rb.x, rb.y});
    auto [endChunkX, endChunkY] = WorldToChunkPosition(Vector2 {rb.x + rb.width, rb.y + rb.height});

    for (int chunkY = startChunkY; chunkY <= endChunkY; ++chunkY) {
        for (int chunkX = startChunkX; chunkX <= endChunkX; ++chunkX) {
            size_t chunkIndex = ChunkPositionToIndex(Vector2 {(float)chunkX, (float)chunkY});
            if (chunkIndex >= 0 && chunkIndex < CHUNK_LENGTH_BLOCKS) {
                const Chunk& chunk = mWorld->GetChunk(chunkIndex);
                const auto& rects = chunk.GetCollisionRects();

                for (const auto& rect : rects) {
                    if (CheckCollisionRecs(rb, rect)) {
                        out_rb = rect;
                        return true; // Collision detected
                    }
                }
            }
        }
    }

    return false; // No collision
}