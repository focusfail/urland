#pragma once

#include "core/Constants.h"

#include <raymath.h>

/// @brief Convert a length of chunks to a length of pixels
/// @return The length of the chunks as pixels
inline int ChunksAsPixels(int chunks) { return chunks * CHUNK_SIZE_BLOCKS * BLOCK_SIZE_PIXELS; }

/// @brief Convert a length of chunks to a length of blocks
/// @return The length of the chunks as blocks
inline int ChunksAsBlocks(int chunks) { return chunks * CHUNK_SIZE_BLOCKS; }

/// @brief Convert chunk position to chunk index in array
inline ChunkIndex ChunkPositionToIndex(ChunkCoordinate x, ChunkCoordinate y)
{
    return static_cast<ChunkIndex>(y * WORLD_WIDTH_CHUNKS + x);
}

inline ChunkIndex ChunkPositionToIndex(ChunkPosition position)
{
    return static_cast<ChunkIndex>(position.first * WORLD_WIDTH_CHUNKS + position.second);
}

/// @brief Convert a chunk index to a chunk position
inline ChunkPosition ChunkIndexToPosition(ChunkIndex index)
{
    ChunkCoordinate x = index % WORLD_WIDTH_CHUNKS;
    ChunkCoordinate y = index / WORLD_WIDTH_CHUNKS;
    return {x, y};
}