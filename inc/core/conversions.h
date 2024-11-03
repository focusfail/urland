#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <math.h>

#include "raylib.h"

#include "core/Constants.h"

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

inline int WorldToBlockIndex(const Vector2& worldPosition)
{
    int localBlockX = ((int)worldPosition.x % CHUNK_SIZE_PIXELS) / BLOCK_SIZE_PIXELS;
    int localBlockY = ((int)worldPosition.y % CHUNK_SIZE_PIXELS) / BLOCK_SIZE_PIXELS;

    // Step 3: Convert the 2D block position into a 1D block index within the chunk
    int blockIndex = localBlockY * CHUNK_SIZE_BLOCKS + localBlockX;

    return blockIndex;
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