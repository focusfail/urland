#pragma once

#include <utility>

static const int BLOCK_SIZE_PIXELS = 16;

static const int CHUNK_SIZE_BLOCKS = 32;
static const int CHUNK_SIZE_PIXELS = CHUNK_SIZE_BLOCKS * BLOCK_SIZE_PIXELS;
static const int CHUNK_LENGTH_BLOCKS = CHUNK_SIZE_BLOCKS * CHUNK_SIZE_BLOCKS;

static const int WORLD_WIDTH_CHUNKS = 64;
static const int WORLD_HEIGHT_CHUNKS = 16;
static const int WORLD_LENGTH_CHUNKS = WORLD_WIDTH_CHUNKS * WORLD_WIDTH_CHUNKS;

// Single coordinates
using ChunkCoordinate = float;
using BlockCoordinate = float;
using ScreenCoordinate = float;
using WorldCoordinate = float;

// Positions
using ChunkPosition = std::pair<ChunkCoordinate, ChunkCoordinate>;
using BlockPosition = std::pair<BlockCoordinate, BlockCoordinate>;
using ScreenPosition = std::pair<ScreenCoordinate, ScreenCoordinate>;
using WorldPosition = std::pair<WorldCoordinate, WorldCoordinate>;

// Indices
using BlockIndex = int;
using ChunkIndex = int;
