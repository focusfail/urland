#ifndef URLAND_WORLD_H
#define URLAND_WORLD_H

#include "Chunk.h"

#include <entt/entt.hpp>

using ChunkArray = std::array<Chunk, WORLD_LENGTH>;
;

class World
{
public:
    World();
    void Generate();
    void Render(const Texture2DAtlas& atlas, const BlockRegistry& br);
    void Update(entt::registry& reg, float dt);
    void PlaceBlock(float x, float y, Block block);
    ChunkArray* GetChunkArray() { return m_chunks.get(); }

private:
    std::unique_ptr<ChunkArray> m_chunks;
    std::vector<size_t> m_active_chunks;
};

#endif // URLAND_WORLD_H