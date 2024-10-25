#include "game/game.h"

#include <string>
#include "rlgl.h"
#include "rlImGui.h"

#include "core/globals.h"
#include "util/debug/draw_y_block_height_debug.h"
#include "util/debug/draw_debug_ui.h"

Game::Game()
{
    InitWindow(1920, 1080, "urland - v0.2.0");
    rlImGuiSetup(true);

    mSpriteManager.AddTexture("blocks", "C:/code/urland/assets/block-sheet.png");
    mWorld.Init(*mSpriteManager.GetTexture("blocks"));
    mCamera.target = {960, 540};
    mCamera.offset = {960, 540};
    mCamera.zoom = 0.5f;
}

void Game::Run()
{
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        mUpdate(dt);
        mRender(dt);
    }
    CloseWindow();
}

void Game::mRender(float dt) const
{
    BeginDrawing();
    {
        ClearBackground(Color(20, 20, 20, 255));
        BeginMode2D(mCamera);
        {
            mWorld.Render(mCamera, DBG_DRAW_COL_REC);
            mWorld.RenderDebugGrid(DBG_DRAW_CHUNK_BD, DBG_DRAW_BLOCK_BD);
            // Draw terrain outline
            DrawRectangleLines(0, 0, TERRAIN_WIDTH_PIXELS, TERRAIN_HEIGHT_PIXELS, RED);
            // Render temporary player
            DrawRectangle(mCamera.target.x, mCamera.target.y, 24.0f, 40.0f, BLUE);

            if (DBG_DRAW_BLOCK_Y_LVL) DrawYBlockHeightDebug();
        }
        EndMode2D();
        DrawDebugUI(mCamera, dt);
        DrawFPS(10, 1050);
    }
    EndDrawing();
}

void Game::mUpdate(float dt)
{
    if (IsKeyPressed(KEY_F7)) { DBG_DRAW_DBG_UI = !DBG_DRAW_DBG_UI; }
    if (DEBUG_UI_VALUES.forceRegenerate) mWorld.Generate(DEBUG_UI_VALUES.generation);
    if (DEBUG_UI_VALUES.forceUpdate) mWorld.ForceUpdate();
    float speed = 1000.0f;

    if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 4000.0f;

    Vector2 direction(0.0f, 0.0f);

    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;
    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;

    if (direction.x != 0 || direction.y != 0) { direction = Vector2Normalize(direction); }

    mCamera.target = Vector2Add(mCamera.target, Vector2Scale(direction, speed * dt));

    if (IsKeyDown(KEY_F)) rlEnableWireMode();

    Vector2 mousePos = GetMousePosition();
    // Only perform mouse-world interaction if the mouse is not on top of ui
    if (!CheckCollisionPointRec(mousePos, DEBUG_UI_VALUES.area)) {
        mousePos = GetScreenToWorld2D(mousePos, mCamera);
        mCamera.zoom = Clamp(mCamera.zoom + GetMouseWheelMove() * 0.02f, 0.01f, 3.0f);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && DEBUG_UI_VALUES.drawEnabled) {
            Block block;
            block.id = DEBUG_UI_VALUES.drawBlockId;
            mWorld.PlaceBlock(mousePos, block);
        }
    }

    mWorld.Update(mCamera);
}