#include "scenes/StartScene.h"

#include <raylib.h>

StartScene::StartScene(GameState* game_state)
    : Scene(game_state)
{ }

void StartScene::Update() { }

void StartScene::Render() const { DrawText(TextFormat("urland"), 1920 / 2.0f, 10, 40, RED); }