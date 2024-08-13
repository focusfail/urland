#ifndef URLAND_DRAW_CHUNK_GRID_H
#define URLAND_DRAW_CHUNK_GRID_H

#include "core/Constants.h"

#include <raylib.h>
#include <raymath.h>

// Potentially renders lines outside of view.
inline void DrawChunkGrid(const Camera2D& camera)
{
    Vector2 start = GetScreenToWorld2D(Vector2Zero(), camera);
    Vector2 end = GetScreenToWorld2D(Vector2(GetScreenWidth(), GetScreenHeight()), camera);

    start.x = floor(start.x / CHUNK_PIXEL_SIZE) * CHUNK_PIXEL_SIZE;
    start.y = floor(start.y / CHUNK_PIXEL_SIZE) * CHUNK_PIXEL_SIZE;

    if (camera.zoom > 0.05f) {
        // Draw vertical chunk grid lines
        for (int x = start.x; x < end.x; x += CHUNK_PIXEL_SIZE) {
            DrawLine(x, start.y, x, end.y, Color {55, 55, 55, 255});
        }

        // Draw horizontal chunk grid lines
        for (int y = start.y; y < end.y; y += CHUNK_PIXEL_SIZE) {
            DrawLine(start.x, y, end.x, y, Color {55, 55, 55, 255});
        }
    }

    // Draw bounding lines
    DrawLine(0, 0, 0, CHUNK_PIXEL_SIZE * WORLD_HEIGHT, RED);                    // left
    DrawLine(CHUNK_PIXEL_SIZE * WORLD_WIDTH, 0, CHUNK_PIXEL_SIZE * WORLD_WIDTH, // right
             CHUNK_PIXEL_SIZE * WORLD_HEIGHT, RED);
    DrawLine(0, 0, CHUNK_PIXEL_SIZE * WORLD_WIDTH, 0, RED);                      // top
    DrawLine(0, CHUNK_PIXEL_SIZE * WORLD_HEIGHT, CHUNK_PIXEL_SIZE * WORLD_WIDTH, // bottom
             CHUNK_PIXEL_SIZE * WORLD_HEIGHT, RED);
}

#endif // URLAND_DRAW_CHUNK_GRID_H