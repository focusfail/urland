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

        // Horizontal Movement with Step-Up Logic
        if (rb.velX != 0.0f) {
            RigidBody horRb = rb;
            horRb.x += rb.velX;
            RigidBody colRb;

            if (mCheckCollision(horRb, colRb)) {
                // Try to step up if we hit a horizontal obstacle
                bool canStepUp = false;

                // Create a "step-up" RigidBody shifted up by one block height
                RigidBody stepUpRb = rb;
                stepUpRb.x += rb.velX;
                stepUpRb.y -= BLOCK_SIZE_PIXELS; // Move up by 1 block (adjust to your block height)

                // Check if there's space to step up
                if (!mCheckCollision(stepUpRb, colRb)) { canStepUp = true; }

                // Step up if possible, otherwise stop horizontal movement
                if (canStepUp) {
                    rb.y -= BLOCK_SIZE_PIXELS; // Move up by 1 block height
                    rb.x += rb.velX;           // Continue moving horizontally
                }
                else {
                    // Handle standard horizontal collision response
                    if (rb.velX > 0) { rb.x = colRb.x - rb.width; }
                    else {
                        rb.x = colRb.x + colRb.width;
                    }
                    rb.velX = 0.0f;
                }
            }
            else {
                rb.x += rb.velX; // No collision, proceed normally
            }
        }

        // Handle vertical movement
        if (rb.velY != 0.0f) {
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

        // Reset the position delta
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