#include <iostream>
#include <array>
#include <vector>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "core/conversions.h"
#include "core/constants.h"
#include "game/world/world.h"

int main()
{
    InitWindow(1920, 1080, "Hello");
    rlDisableBackfaceCulling();

    Camera2D camera = {0};
    camera.target = {960, 540}; // Center of the screen
    camera.offset = {960, 540}; // Center of the screen

    Texture2D atlas = LoadTexture("c:/code/urland/assets/block-sheet.png");
    SetTextureFilter(atlas, RL_TEXTURE_FILTER_NEAREST);

    World world;
    world.Init(atlas);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_A)) camera.target.x -= 1000 * dt;
        if (IsKeyDown(KEY_D)) camera.target.x += 1000 * dt;
        if (IsKeyDown(KEY_W)) camera.target.y -= 1000 * dt;
        if (IsKeyDown(KEY_S)) camera.target.y += 1000 * dt;
        camera.zoom = Clamp(camera.zoom + GetMouseWheelMove() * 0.1f, 0.1f, 2.0f);

        world.Update(camera);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        {
            world.Render(camera);
            world.RenderDebugGrid(true, false);
            DrawRectangleLines(0, 0, TERRAIN_WIDTH_PIXELS, TERRAIN_HEIGHT_PIXELS, RED);
            DrawRectangle(camera.target.x, camera.target.y, 24.0f, 40.0f, BLUE);
        }
        EndMode2D();

        DrawFPS(10, 10);
        EndDrawing();
    }
    UnloadTexture(atlas);
    CloseWindow();
    return EXIT_SUCCESS;
}