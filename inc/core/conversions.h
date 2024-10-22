#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <math.h>

#include "raylib.h"

#include "core/constants.h"

inline Vector2 BlockIndexToPosition(unsigned int blockIndex)
{
    float x = blockIndex % CHUNK_SIZE_BLOCKS;
    float y = blockIndex / CHUNK_SIZE_BLOCKS;

    return {x, y};
}

inline Vector2 WorldToChunkPosition(const Vector2& worldPosition)
{
    float x = floor(worldPosition.x / CHUNK_SIZE_PIXELS);
    float y = floor(worldPosition.y / CHUNK_SIZE_PIXELS);
    return {x, y};
}

inline int ChunkPositionToIndex(const Vector2& chunkPosition)
{
    return (int)chunkPosition.y * TERRAIN_WIDTH_CHUNKS + (int)chunkPosition.x;
}

inline Vector2 ChunkIndexToPosition(int chunkIndex)
{
    return {
        (float)(chunkIndex % TERRAIN_WIDTH_CHUNKS),
        (float)(chunkIndex / TERRAIN_WIDTH_CHUNKS),
    };
}

#endif // CONVERSIONS_H