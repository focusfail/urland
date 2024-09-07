#include "core/Chunk.h"
#include "core/Convertions.h"

void Chunk::Init() { }

void Chunk::Render() const
{
    auto [x, y] = ChunkIndexToPosition(_index);

    DrawRectangle(ChunksAsPixels(x), ChunksAsPixels(y), CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS, WHITE);
    DrawRectangleLines(ChunksAsPixels(x), ChunksAsPixels(y), CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS, BLACK);
}

void Chunk::Update() { }

void Chunk::SetIndex(ChunkIndex index) { _index = index; }