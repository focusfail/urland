#pragma once

#include "core/Chunk.h"
#include <array>
#include <memory>

using ChunkArray = std::array<Chunk, WORLD_LENGTH_CHUNKS>;

class World
{
public:
    World();
    void Init();
    void Update();
    void Render(Texture2D* blocks_texture) const;

private:
    std::unique_ptr<ChunkArray> m_chunks;
};