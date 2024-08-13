#ifndef URLAND_CONSTANTS_H
#define URLAND_CONSTANTS_H

// Width & height of a chunk in blocks
static const int CHUNK_SIZE = 32;
static const int CHUNK_LENGTH = CHUNK_SIZE * CHUNK_SIZE;

static const int BLOCK_SIZE = 16;
static const int CHUNK_PIXEL_SIZE = CHUNK_SIZE * BLOCK_SIZE;

// World size in chunks
static const int WORLD_WIDTH = 32;
static const int WORLD_HEIGHT = 16;
static const int WORLD_LENGTH = WORLD_WIDTH * WORLD_HEIGHT;

#endif // URLAND_CONSTANTS_H