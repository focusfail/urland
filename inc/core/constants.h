#ifndef CONSTANTS_H
#define CONSTANTS_H

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
inline const int TERRAIN_HEIGHT_BLOCKS = TERRAIN_WIDTH_CHUNKS * CHUNK_SIZE_BLOCKS;
// Terrain width pixels
inline const int TERRAIN_WIDTH_PIXELS = TERRAIN_WIDTH_CHUNKS * CHUNK_SIZE_PIXELS;
// Terrain height pixels
inline const int TERRAIN_HEIGHT_PIXELS = TERRAIN_HEIGHT_CHUNKS * CHUNK_SIZE_PIXELS;

inline const int TEXTURE_ATLAS_SIZE = 16;

// Radius of chunks to render around the player
inline const int RENDER_SQUARE_RADIUS = 3;
// Radius of chunks to load around the player
inline const int UPDATE_SQUARE_RADIUS = 5;

#endif // CONSTANTS_H
