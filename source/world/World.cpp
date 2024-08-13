#include "world/World.h"
#include "core/Block.h"

#include "components/CharacterController.h"
#include "components/RigidBody.h"

World::World()
    : m_chunks(std::make_unique<ChunkArray>())
{ }

void World::Render(const Texture2DAtlas& atlas, const BlockRegistry& br)
{
    for (size_t i : m_active_chunks) {
        Chunk& chunk = m_chunks->at(i);
        chunk.Render(i, atlas, br);
        chunk.DrawBoundingBoxes();
    }
}

void World::Update(entt::registry& reg, float dt)
{
    auto view = reg.view<CharacterController, RigidBody>();
    auto player = view.front();
    const auto& body = view.get<RigidBody>(player);

    int chunk_x = static_cast<int>((body.x / CHUNK_PIXEL_SIZE));
    int chunk_y = static_cast<int>((body.y / CHUNK_PIXEL_SIZE));

    int render_dist = 1;

    m_active_chunks.clear();
    for (int y = chunk_y - render_dist; y <= chunk_y + render_dist; y++) {
        if (y < 0 || y > WORLD_HEIGHT) continue;

        for (int x = chunk_x - render_dist; x <= chunk_x + render_dist; x++) {
            int index = static_cast<int>(y * WORLD_WIDTH + x);

            if (x < 0 || x > WORLD_WIDTH) continue;

            Chunk& chunk = m_chunks->at(index);
            chunk.Update();

            m_active_chunks.push_back(index);
        }
    }
}

void World::PlaceBlock(float x, float y, Block block)
{
    int chunk_x = static_cast<int>((x / CHUNK_PIXEL_SIZE));
    int chunk_y = static_cast<int>((y / CHUNK_PIXEL_SIZE));
    int chunk_index = chunk_y * WORLD_WIDTH + chunk_x;

    if (chunk_index < 0 || chunk_index > WORLD_LENGTH || x < 0 || y < 0) {
        TraceLog(LOG_WARNING, "Attempted to place block at invalid position.");
        return;
    }

    Chunk& chunk = m_chunks->at(chunk_index);
    chunk.PlaceBlock(x, y, block);
}