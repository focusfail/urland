#include "core/World.h"

World::World()
    : _chunks(std::make_unique<ChunkArray>())
{ }

void World::Init()
{
    for (size_t chunk_i = 0; chunk_i < _chunks->size(); chunk_i++) {
        Chunk& chunk = _chunks->at(chunk_i);
        chunk.SetIndex(chunk_i);
    }
}

void World::Render() const
{
    for (size_t chunk_i = 0; chunk_i < _chunks->size(); chunk_i++) {
        const Chunk& chunk = _chunks->at(chunk_i);
        chunk.Render();
    }
}
