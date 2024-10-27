#include "game/game.h"

#include <string>
#include "rlgl.h"
#include "rlImGui.h"

#include "core/globals.h"
#include "util/debug/draw_y_block_height_debug.h"
#include "util/debug/draw_debug_ui.h"

#include "components/player_tag.h"
#include "components/rigid_body.h"

// temporary
void DrawRigidBodies(const entt::registry& reg)
{
    auto view = reg.view<RigidBody>();
    view.each([&](const auto entity, auto& rb) { DrawRectangleRec(rb, BLUE); });
}

Game::Game()
{
    InitWindow(1920, 1080, "urland - v0.2.0");
    rlImGuiSetup(true);

    mSpriteManager.AddTexture("blocks", "C:/code/urland/assets/block-sheet.png");
    mWorld.Init(*mSpriteManager.GetTexture("blocks"));
    mCamera.target = {960, 540};
    mCamera.offset = {960, 540};
    mCamera.zoom = 0.5f;

    mRigidBodyCollisionSystem.Init(mWorld);

    auto player = mRegistry.create();
    mRegistry.emplace<PlayerTag>(player);
    mRegistry.emplace<FollowCamera>(player, 2.5f);
    mRegistry.emplace<RigidBody>(player, .0f, .0f, 24.0f, 40.0f);
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
            mWorld.Render(mCamera);
            // Draw terrain outline
            DrawRectangleLines(0, 0, TERRAIN_WIDTH_PIXELS, TERRAIN_HEIGHT_PIXELS, RED);
            DrawRigidBodies(mRegistry);

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
    if (DBG_DRAW_WIREFRAME)
        rlEnableWireMode();
    else {
        rlDisableWireMode();
    }

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

    mPlayerMovementSystem.Update(mRegistry, dt);
    mGravitySystem.Update(mRegistry, dt);
    mRigidBodyCollisionSystem.Update(mRegistry);
    mFollowCameraSystem.Update(mRegistry, mCamera, dt);
    mWorld.Update(mCamera);
}