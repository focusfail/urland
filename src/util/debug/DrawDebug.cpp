#include "util/debug/DrawDebug.h"

DebugUIValues DBG_UI_VALUES;

void DrawDebugUI(const Camera2D& camera, float dt)
{
    // populate the blocks
    if (DBG_UI_VALUES.blockNamePtrs.empty()) {
        DBG_UI_VALUES.blockNamePtrs.reserve(BLOCK_NAME.size());

        for (auto& name : BLOCK_NAME) { DBG_UI_VALUES.blockNamePtrs.push_back(name.c_str()); }
    }

    if (!DBG_DRAW_DBG_UI) return;

    DBG_UI_VALUES.forceUpdate = false;
    DBG_UI_VALUES.forceRegenerate = false;
    ImGui::Begin("debugWindow");
    {
        ImVec2 pos = ImGui::GetWindowPos();
        DBG_UI_VALUES.area = {pos.x, pos.y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()};
        if (ImGui::CollapsingHeader("Draw")) {
            if (ImGui::Checkbox("Enable drawing", &DBG_UI_VALUES.drawEnabled)) {
                ImGui::BeginDisabled();
                ImGui::ListBox("Block", &DBG_UI_VALUES.currentBlockIndex, DBG_UI_VALUES.blockNamePtrs.data(),
                               DBG_UI_VALUES.blockNamePtrs.size(), 3);
                ImGui::EndDisabled();
            }
            else {
                ImGui::ListBox("Block", &DBG_UI_VALUES.currentBlockIndex, DBG_UI_VALUES.blockNamePtrs.data(),
                               DBG_UI_VALUES.blockNamePtrs.size(), 3);
            }
        }

        if (ImGui::CollapsingHeader("Debug")) {
            ImGui::Checkbox("Block Outlines", &DBG_DRAW_BLOCK_BD);
            ImGui::Checkbox("Chunk Outlines", &DBG_DRAW_CHUNK_BD);
            ImGui::Checkbox("Chunk Collision Outlines", &DBG_DRAW_COL_REC);
            ImGui::Checkbox("Wireframe", &DBG_DRAW_WIREFRAME);
            ImGui::Checkbox("Block Height Label", &DBG_DRAW_BLOCK_Y_LVL);
        }

        if (ImGui::CollapsingHeader("Physics")) {
            ImGui::BeginDisabled();
            ImGui::Checkbox("Collision", &DBG_DRAW_BLOCK_Y_LVL);
            ImGui::EndDisabled();
            if (ImGui::Button("Default")) RB_GRAVITY = 980.0f;
            ImGui::SameLine();
            ImGui::SliderFloat("Gravity", &RB_GRAVITY, -5000.0f, 5000.0f);
        }

        if (ImGui::CollapsingHeader("World")) {
            DBG_UI_VALUES.forceUpdate = ImGui::Button("Force Update");
            ImGui::SliderInt("Render Distance", &RENDER_DISTANCE, 0, 124);

            if (ImGui::TreeNode("Generation")) {
                ImGui::SliderFloat("Surface Level", &DBG_UI_VALUES.generation.surfaceLevel, 0.0f, 1.0f);

                // Mountain Noise Settings
                if (ImGui::TreeNode("Mountain Noise")) {
                    bool changed = false;
                    changed |= ImGui::SliderInt("Octaves", &DBG_UI_VALUES.generation.mountainOctaves, 1, 8);
                    changed |= ImGui::SliderFloat("Gain", &DBG_UI_VALUES.generation.mountainGain, 0.0f, 1.0f);
                    changed |= ImGui::SliderFloat("Frequency", &DBG_UI_VALUES.generation.mountainFrequency, 0.0f, 1.0f);
                    changed |= ImGui::InputInt("Seed", &DBG_UI_VALUES.generation.mountainSeed);
                    if (changed) DBG_UI_VALUES.forceUpdate = true;
                    ImGui::TreePop();
                }

                // Biome Noise Settings
                if (ImGui::TreeNode("Biome Noise")) {
                    bool changed = false;
                    changed |= ImGui::SliderInt("Octaves", &DBG_UI_VALUES.generation.biomeOctaves, 1, 8);
                    changed |= ImGui::SliderFloat("Gain", &DBG_UI_VALUES.generation.biomeGain, 0.0f, 1.0f);
                    changed |=
                        ImGui::DragFloat("Frequency", &DBG_UI_VALUES.generation.biomeFrequency, 0.001f, 0.001f, 0.1f);
                    changed |= ImGui::InputInt("Seed", &DBG_UI_VALUES.generation.biomeSeed);
                    if (changed) DBG_UI_VALUES.forceUpdate = true;
                    ImGui::TreePop();
                }

                DBG_UI_VALUES.forceRegenerate = ImGui::Button("Apply");
                ImGui::SameLine();

                if (ImGui::Button("Random Seed")) {
                    DBG_UI_VALUES.generation.biomeSeed = (int)time(NULL) + (int)(dt * 10000.0f);
                    DBG_UI_VALUES.generation.mountainSeed = (int)time(NULL) + (int)(dt * 10000.0f);
                    DBG_UI_VALUES.forceRegenerate = true;
                }

                // Presets
                if (ImGui::Button("Default")) {
                    DBG_UI_VALUES.generation = GenerationOptions::Default();
                    DBG_UI_VALUES.forceRegenerate = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("Mountainous")) {
                    DBG_UI_VALUES.generation = GenerationOptions::Mountainous();
                    DBG_UI_VALUES.forceRegenerate = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("Plains")) {
                    DBG_UI_VALUES.generation = GenerationOptions::Plains();
                    DBG_UI_VALUES.forceRegenerate = true;
                }

                ImGui::TreePop();
            }

        } // debugWindow
        ImGui::End();
    };
}

bool CheckEntityClicked(float pX, float pY, entt::entity& outEntity, entt::registry& reg)
{
    auto view = reg.view<RigidBody>();

    for (auto& entity : view) {
        RigidBody& rb = view.get<RigidBody>(entity);

        if (CheckCollisionPointRec(Vector2(pX, pY), rb)) {
            outEntity = entity;
            return true;
        }
    }
    return false;
}

void DrawSelectedEntityWindow(entt::registry& reg)
{
    if (SELECTED_ENTITY < 0 || !DBG_DRAW_DBG_UI) return;

    entt::entity selectedEntity = (entt::entity)SELECTED_ENTITY;
    RigidBody& rb = reg.get<RigidBody>(selectedEntity);
    FollowCamera* fc = reg.try_get<FollowCamera>(selectedEntity);
    Stats* stats = reg.try_get<Stats>(selectedEntity);

    float rbPosition[2] = {rb.x, rb.y};
    int rbShape[2] = {(int)rb.width, (int)rb.height};
    float retardation = fc->retardation;

    ImGui::Begin("Entity View");
    {
        ImVec2 pos = ImGui::GetWindowPos();
        DBG_UI_VALUES.entityWindowArea = {pos.x, pos.y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()};

        if (stats) {
            if (ImGui::CollapsingHeader("Stats")) {
                ImGui::LabelText("Health", "(%.1f)", stats->health);
                ImGui::LabelText("Reach", "(%.1f)", stats->reach);
                ImGui::LabelText("Speed", "(%.1f)", stats->speed);
                ImGui::LabelText("Sprint multiplier", "(%.1f)", stats->sprintMul);
            }
        }
        if (ImGui::CollapsingHeader("RigidBody")) {
            ImGui::DragFloat2("Position X, Y", rbPosition, 1.0f, 0.0f, TERRAIN_WIDTH_PIXELS);
            ImGui::SliderInt2("Width, Height", rbShape, 0, 2000);
            ImGui::Checkbox("Collision", &rb.collides);
            ImGui::Checkbox("Gravity", &rb.hasGravity);
        }
        if (fc) {
            if (ImGui::CollapsingHeader("FollowCamera")) {
                ImGui::SliderFloat("Retardation", &retardation, 0.0f, 20.0f);
            }
        }
    }

    ImGui::End();

    // Update values
    rb.x = rbPosition[0];
    rb.y = rbPosition[1];
    rb.width = rbShape[0];
    rb.height = rbShape[1];
    fc->retardation = retardation;
}