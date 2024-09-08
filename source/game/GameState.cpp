#include "game/GameState.h"

std::pair<Scene*, int> GameState::AddScene(unique_ptr<Scene> scene)
{
    // Add the scene
    m_scenes.push_back(std::move(scene));
    return std::make_pair(m_scenes.back().get(), static_cast<int>(m_scenes.size()) - 1);
}

void GameState::SetScene(int scene_index) { m_current_scene = scene_index; }

Scene* GameState::GetCurrentScene()
{
    if (m_current_scene >= m_scenes.size()) return nullptr;
    return m_scenes.at(m_current_scene).get();
}