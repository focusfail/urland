#pragma once

#include "core/Scene.h"

#include <memory>
#include <vector>

using std::unique_ptr, std::vector;

class GameState
{
public:
    std::pair<Scene*, int> AddScene(unique_ptr<Scene> scene);
    void SetScene(int scene_index);
    /// @brief Return pointer to current scene
    Scene* GetCurrentScene();

private:
    int m_current_scene = 0;
    vector<unique_ptr<Scene>> m_scenes;
};