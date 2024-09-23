#pragma once

#include "core/Chunk.h"
#include <array>
#include <entt/entt.hpp>
#include <memory>
#include <vector>

using ChunkArray = std::array<Chunk, WORLD_LENGTH_CHUNKS>;

class World
{
public:
    World();
    void Init(Texture2D* block_atlas);
    void Update(entt::registry& registry, Camera2D& camera);
    void Render() const;

private:
    std::unique_ptr<ChunkArray> m_chunks;
    std::vector<int> m_active_chunks;
    Texture2D* m_block_atlas;
    Shader m_shader;
};