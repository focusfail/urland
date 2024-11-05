#include "game/Game.h"

#include <string>
#include <time.h>
#include "rlgl.h"
#include "rlImGui.h"

#include "core/Globals.h"
#include "util/debug/DrawYBlockHeightDebug.h"
#include "util/debug/DrawDebug.h"
#include "util/PathManager.h"

#include "components/PlayerTag.h"
#include "components/RigidBody.h"

// Temporary function for rendering RigidBodies
void DrawRigidBodies(const entt::registry& reg)
{
    auto view = reg.view<RigidBody>();
    view.each([&](const auto entity, auto& rb) {
        DrawRectangleRec(rb, BLUE);
        // Draw outline around selected RigidBody
        if ((int)entity == SELECTED_ENTITY) DrawRectangleLinesEx(rb, 2.0f, YELLOW);
    });
}

Game::Game()
{
    InitWindow(1920, 1080, "urland - v0.2.0");
    rlImGuiSetup(true);

    // Add block atlas to sprite manager
    mSpriteManager.AddTexture("blocks", GetPath("assets/block-sheet.png"));
    mWorld.Init(*mSpriteManager.GetTexture("blocks"));

    float halfDispW = (float)GetScreenWidth() / 2.0f;
    float halfDispH = (float)GetScreenHeight() / 2.0f;
    mCamera.target = {halfDispW, halfDispH};
    mCamera.offset = {halfDispW, halfDispH};
    mCamera.zoom = 0.5f;

    mRigidBodyCollisionSystem.Init(mWorld);

    { // Create player entity
        auto player = mRegistry.create();
        mRegistry.emplace<PlayerTag>(player);
        mRegistry.emplace<FollowCamera>(player, 8.0f);
        mRegistry.emplace<RigidBody>(player, .0f, .0f, 24.0f, 40.0f);
    }

    srand(time(NULL));
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

void Game::mRender(float dt) // const
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

        // Draw UI
        rlImGuiBegin();
        {
            DrawSelectedEntityWindow(mRegistry);
            DrawDebugUI(mCamera, dt);
        }
        rlImGuiEnd();

        DrawFPS(10, 1050);
    }
    EndDrawing();
}

void Game::mUpdate(float dt)
{
    if (IsKeyPressed(KEY_F7)) { DBG_DRAW_DBG_UI = !DBG_DRAW_DBG_UI; }
    if (DBG_UI_VALUES.forceRegenerate) mWorld.Generate(DBG_UI_VALUES.generation);
    if (DBG_UI_VALUES.forceUpdate) mWorld.ForceUpdate();
    if (DBG_DRAW_WIREFRAME)
        rlEnableWireMode();
    else {
        rlDisableWireMode();
    }

    Vector2 mousePos = GetMousePosition();
    // Only perform mouse-world interaction if the mouse is not on top of ui
    if (!CheckCollisionPointRec(mousePos, DBG_UI_VALUES.area) &&
        !CheckCollisionPointRec(mousePos, DBG_UI_VALUES.entityWindowArea)) {
        mousePos = GetScreenToWorld2D(mousePos, mCamera);
        mCamera.zoom = Clamp(mCamera.zoom + GetMouseWheelMove() * 0.02f, 0.01f, 3.0f);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (DBG_UI_VALUES.drawEnabled) {
                Block block;
                block.id = DBG_UI_VALUES.currentBlockIndex;
                mWorld.PlaceBlock(mousePos, block);
            }
            else {
                entt::entity entity;
                if (CheckEntityClicked(mousePos.x, mousePos.y, entity, mRegistry)) { SELECTED_ENTITY = (int)entity; }
                else {
                    SELECTED_ENTITY = -1;
                }
            }
        }
    }

    mPlayerMovementSystem.Update(mRegistry, dt);
    mGravitySystem.Update(mRegistry, dt);
    mRigidBodyCollisionSystem.Update(mRegistry);
    mFollowCameraSystem.Update(mRegistry, mCamera, dt);
    mWorld.Update(mCamera);
}