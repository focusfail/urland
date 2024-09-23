#pragma once

#include "core/Constants.h"

#include <raylib.h>
#include <raymath.h>

/// @brief Convert a length of chunks to a length of pixels
/// @return The length of the chunks as pixels
inline int ChunksAsPixels(int chunks) { return chunks * CHUNK_SIZE_BLOCKS * BLOCK_SIZE_PIXELS; }

/// @brief Convert a length of chunks to a length of blocks
/// @return The length of the chunks as blocks
inline int ChunksAsBlocks(int chunks) { return chunks * CHUNK_SIZE_BLOCKS; }

/// @brief Convert a length of blocks to a length of pixels
/// @return The length of the blocks as pixels
inline int BlocksAsPixels(int blocks) { return blocks * BLOCK_SIZE_PIXELS; }

/// @brief Convert chunk position to chunk index in array
inline ChunkIndex ChunkPositionToIndex(ChunkCoordinate x, ChunkCoordinate y)
{
    return static_cast<ChunkIndex>(y * WORLD_WIDTH_CHUNKS + x);
}

inline ChunkIndex ChunkPositionToIndex(ChunkPosition position)
{
    return static_cast<ChunkIndex>(position.second * WORLD_WIDTH_CHUNKS + position.first);
}

/// @brief Convert a chunk index to a chunk position
inline ChunkPosition ChunkIndexToPosition(ChunkIndex index)
{
    ChunkCoordinate x = index % WORLD_WIDTH_CHUNKS;
    ChunkCoordinate y = index / WORLD_WIDTH_CHUNKS;
    return {x, y};
}

inline BlockPosition BlockIndexToPositionInChunk(BlockIndex index)
{
    BlockCoordinate x = index % CHUNK_SIZE_BLOCKS;
    BlockCoordinate y = index / CHUNK_SIZE_BLOCKS;
    return {x, y};
}

inline std::pair<NDC, NDC> PixelToNDC(ScreenCoordinate x, ScreenCoordinate y, int width, int height)
{
    return {2.0f * x / width - 1.0f, 1.0f - (2.0f * y / height)};
}

inline ChunkPosition WorldToChunkPosition(WorldCoordinate x, WorldCoordinate y)
{
    return {floor(x / CHUNK_SIZE_PIXELS), floor(y / CHUNK_SIZE_PIXELS)};
}