#pragma once

#include "core/Scene.h"

class StartScene : public Scene
{
public:
    StartScene(GameState* game_state);
    void Update() override;
    void Render() const override;

private:
};