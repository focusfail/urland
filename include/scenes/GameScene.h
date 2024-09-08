#pragma once

#include "core/Scene.h"
#include "core/SpriteManager.h"
#include "core/World.h"

class GameScene : public Scene
{
public:
    GameScene(GameState* game_state, SpriteManager* sprite_manager);
    void Init() override;
    void Update() override;
    void Render() const override;

private:
    World m_world;
    SpriteManager* m_sprite_manager;
};