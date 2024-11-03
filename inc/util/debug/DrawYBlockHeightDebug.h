#ifndef DRAW_Y_BLOCK_HEIGHT_DEBUG_H
#define DRAW_Y_BLOCK_HEIGHT_DEBUG_H

#include <string>
#include "core/Constants.h"
#include "raylib.h"

inline void DrawYBlockHeightDebug()
{
    for (int y = 0; y < TERRAIN_HEIGHT_CHUNKS; y++) {
        int pixels = y * CHUNK_SIZE_PIXELS;
        int blocks = y * CHUNK_SIZE_BLOCKS;
        DrawText(std::to_string(blocks).c_str(), -100, pixels, 40, RED);
    }
}

#endif // DRAW_Y_BLOCK_HEIGHT_DEBUG_H