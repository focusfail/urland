#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"
#include <string>

// Block width and height in pixels
inline const int BLOCK_SIZE_PIXELS = 16;
// Total pixels per block
inline const int BLOCK_LENGTH_PIXELS = BLOCK_SIZE_PIXELS * BLOCK_SIZE_PIXELS;
// Chunk width and height in blocks
inline const int CHUNK_SIZE_BLOCKS = 32;
// Total blocks per chunk
inline const int CHUNK_LENGTH_BLOCKS = CHUNK_SIZE_BLOCKS * CHUNK_SIZE_BLOCKS;
// Chunk width and height in pixels
inline const int CHUNK_SIZE_PIXELS = CHUNK_SIZE_BLOCKS * BLOCK_SIZE_PIXELS;
// Terrain width in chunks
inline const int TERRAIN_WIDTH_CHUNKS = 128;
// Terrain height in chunks
inline const int TERRAIN_HEIGHT_CHUNKS = 32;
// Total chunks
inline const int TERRAIN_LENGTH_CHUNKS = TERRAIN_WIDTH_CHUNKS * TERRAIN_HEIGHT_CHUNKS;
// Terrain width in blocks
inline const int TERRAIN_WIDTH_BLOCKS = TERRAIN_WIDTH_CHUNKS * CHUNK_SIZE_BLOCKS;
// Terrain height in blocks
inline const int TERRAIN_HEIGHT_BLOCKS = TERRAIN_HEIGHT_CHUNKS * CHUNK_SIZE_BLOCKS;
// Terrain width pixels
inline const int TERRAIN_WIDTH_PIXELS = TERRAIN_WIDTH_CHUNKS * CHUNK_SIZE_PIXELS;
// Terrain height pixels
inline const int TERRAIN_HEIGHT_PIXELS = TERRAIN_HEIGHT_CHUNKS * CHUNK_SIZE_PIXELS;

inline const int TEXTURE_ATLAS_SIZE = 16;

inline const Rectangle WORLD_RECT = {0, 0, TERRAIN_WIDTH_PIXELS, TERRAIN_HEIGHT_PIXELS};

inline const int CHUNK_MESH_VERTEX_COUNT = CHUNK_LENGTH_BLOCKS * 4;

namespace Direction
{
inline const int NORTH = 0;
inline const int UP = 0;
inline const int EAST = 1;
inline const int RIGHT = 1;
inline const int SOUTH = 2;
inline const int DOWN = 2;
inline const int WEST = 3;
inline const int LEFT = 3;
} // namespace Direction

inline const std::string GAME_VERSION = "0.2.1";

#endif // CONSTANTS_H
