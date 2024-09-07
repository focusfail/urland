#include "game/GameState.h"

void GameState::AddScene(unique_ptr<Scene> scene)
{
    // Add the scene
    _scenes.push_back(std::move(scene));
}

void GameState::SetScene(int scene_index) { _current_scene = scene_index; }

Scene* GameState::GetCurrentScene()
{
    if (_current_scene >= _scenes.size()) return nullptr;
    return _scenes.at(_current_scene).get();
}