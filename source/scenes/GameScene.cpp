#include "scenes/GameScene.h"

GameScene::GameScene(GameState* game_state)
    : Scene(game_state)
{
    _world.Init();
}

void GameScene::Render() const { _world.Render(); }

void GameScene::Update() { }