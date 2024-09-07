#pragma once

#include "core/Scene.h"
#include "core/World.h"


class GameScene : public Scene
{
public:
    GameScene(GameState* game_state);
    void Update() override;
    void Render() const override;

private:
    World _world;
};