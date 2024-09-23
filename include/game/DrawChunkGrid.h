#pragma once

#include "core/Constants.h"

#include <raylib.h>
#include <raymath.h>

// Potentially renders lines outside of view.
inline void DrawChunkGrid(const Camera2D& camera)
{
    Vector2 start = GetScreenToWorld2D(Vector2Zero(), camera);
    Vector2 end = GetScreenToWorld2D(Vector2(GetScreenWidth(), GetScreenHeight()), camera);

    start.x = floor(start.x / CHUNK_SIZE_PIXELS) * CHUNK_SIZE_PIXELS;
    start.y = floor(start.y / CHUNK_SIZE_PIXELS) * CHUNK_SIZE_PIXELS;

    if (camera.zoom > 0.05f) {
        // Draw vertical chunk grid lines
        for (int x = start.x; x < end.x; x += CHUNK_SIZE_PIXELS) {
            DrawLine(x, start.y, x, end.y, Color {55, 55, 55, 255});
        }

        // Draw horizontal chunk grid lines
        for (int y = start.y; y < end.y; y += CHUNK_SIZE_PIXELS) {
            DrawLine(start.x, y, end.x, y, Color {55, 55, 55, 255});
        }
    }

    // Draw bounding lines
    DrawLine(0, 0, 0, CHUNK_SIZE_PIXELS * WORLD_HEIGHT_CHUNKS, RED);                            // left
    DrawLine(CHUNK_SIZE_PIXELS * WORLD_WIDTH_CHUNKS, 0, CHUNK_SIZE_PIXELS * WORLD_WIDTH_CHUNKS, // right
             CHUNK_SIZE_PIXELS * WORLD_HEIGHT_CHUNKS, RED);
    DrawLine(0, 0, CHUNK_SIZE_PIXELS * WORLD_WIDTH_CHUNKS, 0, RED);                              // top
    DrawLine(0, CHUNK_SIZE_PIXELS * WORLD_HEIGHT_CHUNKS, CHUNK_SIZE_PIXELS * WORLD_WIDTH_CHUNKS, // bottom
             CHUNK_SIZE_PIXELS * WORLD_HEIGHT_CHUNKS, RED);
}
