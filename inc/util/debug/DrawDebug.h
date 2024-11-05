#ifndef DRAW_DEBUG_UI_H
#define DRAW_DEBUG_UI_H

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "rlgl.h"
#include "entt/entt.hpp"

#include "core/Constants.h"
#include "core/Globals.h"
#include "game/world/Generator.h"
#include "game/BlockInfo.h"
#include "game/world/World.h"
#include "components/RigidBody.h"
#include "components/FollowCamera.h"

#include <vector>
#include <string>
#include <time.h>

struct DebugUIValues
{
    bool drawEnabled = false;
    bool forceUpdate = false;
    bool forceRegenerate = false;
    int currentBlockIndex = 0;
    std::vector<const char*> blockNamePtrs;
    GenerationOptions generation = {};
    Rectangle area;
    Rectangle entityWindowArea;
};

/// @brief DebugUI Variables
extern DebugUIValues DBG_UI_VALUES;

///@brief Draw the DebugUI
extern void DrawDebugUI(const Camera2D& camera, float dt);

/// @brief Check if an entity was clicked
/// @param pX Entity position x
/// @param pY Entity position y
/// @param outEntity On success gets assigned to the clicked entity
/// @param reg Entity Registry
/// @return whether an entity was clicked or not
extern bool CheckEntityClicked(float pX, float pY, entt::entity& outEntity, entt::registry& reg);

///@brief Draw the Entity-Component-Viewer
extern void DrawSelectedEntityWindow(entt::registry& reg);

#endif // DRAW_DEBUG_UI_H
