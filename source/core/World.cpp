#include "core/World.h"

#include <rlgl.h>

World::World()
    : m_chunks(std::make_unique<ChunkArray>())
{ }

void World::Init()
{
    for (size_t chunk_i = 0; chunk_i < m_chunks->size(); chunk_i++) {
        Chunk& chunk = m_chunks->at(chunk_i);
        chunk.SetIndex(chunk_i);
    }
}

void World::Render(Texture2D* blocks_texture) const
{
    rlSetTexture(blocks_texture->id);
    rlBegin(RL_QUADS);

    rlEnd();
    rlSetTexture(0);
}
