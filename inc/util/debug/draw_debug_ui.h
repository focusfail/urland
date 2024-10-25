#ifndef DRAW_DEBUG_UI_H
#define DRAW_DEBUG_UI_H

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "rlgl.h"
#include "core/constants.h"
#include "game/world/generator.h"
#include "game/world/world.h"

#include <vector>
#include <string>
#include <time.h>

struct DebugUIValues
{
    bool drawDebugUi = false;
    bool drawHeaderCollapsed = true;
    bool drawEnabled = false;
    int drawBlockId = 0;
    std::vector<const char*> drawBlockTypes = {"0", "1", "2", "3"};

    bool showBlockOutlines = false;
    bool showChunkOutlines = false;
    bool showYBlockHeight = false;
    bool showChunkCollisionRects = false;
    GenerationOptions generation = {};
    bool forceUpdate = false;
    bool forceRegenerate = false;
    int renderDistance = RENDER_SQUARE_RADIUS;

    Rectangle area;
};

inline static DebugUIValues DEBUG_UI_VALUES;

inline void DrawDebugUI(const Camera2D& camera, float dt)
{
    if (!DEBUG_UI_VALUES.drawDebugUi) return;
    rlImGuiBegin();

    DEBUG_UI_VALUES.forceUpdate = false;
    DEBUG_UI_VALUES.forceRegenerate = false;
    ImGui::Begin("debugWindow");
    {
        ImVec2 pos = ImGui::GetWindowPos();
        DEBUG_UI_VALUES.area = {pos.x, pos.y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()};
        if (ImGui::CollapsingHeader("Draw")) {
            if (ImGui::Checkbox("Enable drawing", &DEBUG_UI_VALUES.drawEnabled)) {
                ImGui::BeginDisabled();
                ImGui::ListBox("Block", &DEBUG_UI_VALUES.drawBlockId, DEBUG_UI_VALUES.drawBlockTypes.data(),
                               DEBUG_UI_VALUES.drawBlockTypes.size(), 3);
                ImGui::EndDisabled();
            }
            else {
                ImGui::ListBox("Block", &DEBUG_UI_VALUES.drawBlockId, DEBUG_UI_VALUES.drawBlockTypes.data(),
                               DEBUG_UI_VALUES.drawBlockTypes.size(), 3);
            }
        }

        if (ImGui::CollapsingHeader("World")) {
            DEBUG_UI_VALUES.forceUpdate = ImGui::Button("Force Update");
            ImGui::SliderInt("Render Distance", &DEBUG_UI_VALUES.renderDistance, 0, 124);
            if (ImGui::TreeNode("Debug")) {
                ImGui::Checkbox("Block Outlines", &DEBUG_UI_VALUES.showBlockOutlines);
                ImGui::Checkbox("Chunk Outlines", &DEBUG_UI_VALUES.showChunkOutlines);
                ImGui::Checkbox("Chunk Collision Outlines", &DEBUG_UI_VALUES.showChunkCollisionRects);
                ImGui::Checkbox("Block Height Label", &DEBUG_UI_VALUES.showYBlockHeight);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Generation")) {
                ImGui::DragFloat("Surface Level", &DEBUG_UI_VALUES.generation.surfaceLevel, 0.001f, 0.0f, 1.0f);

                // Mountain Noise Settings
                if (ImGui::TreeNode("Mountain Noise")) {
                    bool changed = false;
                    changed |= ImGui::SliderInt("Octaves", &DEBUG_UI_VALUES.generation.mountainOctaves, 1, 8);
                    changed |= ImGui::SliderFloat("Gain", &DEBUG_UI_VALUES.generation.mountainGain, 0.0f, 1.0f);
                    changed |= ImGui::DragFloat("Frequency", &DEBUG_UI_VALUES.generation.mountainFrequency, 0.001f,
                                                0.001f, 0.1f);
                    changed |= ImGui::InputInt("Seed", &DEBUG_UI_VALUES.generation.mountainSeed);
                    if (changed) DEBUG_UI_VALUES.forceUpdate = true;
                    ImGui::TreePop();
                }

                // Biome Noise Settings
                if (ImGui::TreeNode("Biome Noise")) {
                    bool changed = false;
                    changed |= ImGui::SliderInt("Octaves", &DEBUG_UI_VALUES.generation.biomeOctaves, 1, 8);
                    changed |= ImGui::SliderFloat("Gain", &DEBUG_UI_VALUES.generation.biomeGain, 0.0f, 1.0f);
                    changed |=
                        ImGui::DragFloat("Frequency", &DEBUG_UI_VALUES.generation.biomeFrequency, 0.001f, 0.001f, 0.1f);
                    changed |= ImGui::InputInt("Seed", &DEBUG_UI_VALUES.generation.biomeSeed);
                    if (changed) DEBUG_UI_VALUES.forceUpdate = true;
                    ImGui::TreePop();
                }

                DEBUG_UI_VALUES.forceRegenerate = ImGui::Button("Apply");
                ImGui::SameLine();

                if (ImGui::Button("Random Seed")) {
                    DEBUG_UI_VALUES.generation.biomeSeed = (int)time(NULL) + (int)(dt * 10000.0f);
                    DEBUG_UI_VALUES.generation.mountainSeed = (int)time(NULL) + (int)(dt * 10000.0f);
                    DEBUG_UI_VALUES.forceRegenerate = true;
                }

                // Presets
                if (ImGui::Button("Default")) {
                    DEBUG_UI_VALUES.generation = GenerationOptions::Default();
                    DEBUG_UI_VALUES.forceRegenerate = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("Mountainous")) {
                    DEBUG_UI_VALUES.generation = GenerationOptions::Mountainous();
                    DEBUG_UI_VALUES.forceRegenerate = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("Plains")) {
                    DEBUG_UI_VALUES.generation = GenerationOptions::Plains();
                    DEBUG_UI_VALUES.forceRegenerate = true;
                }

                ImGui::TreePop();
            }

        } // debugWindow
        ImGui::End();
        rlImGuiEnd();
    };
}
#endif // DRAW_DEBUG_UI_H