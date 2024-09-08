#include "scenes/GameScene.h"

#include <iostream>

GameScene::GameScene(GameState* game_state, SpriteManager* sprite_manager)
    : Scene(game_state)
    , m_sprite_manager(sprite_manager)
{ }

void GameScene::Init() { m_world.Init(); }

void GameScene::Render() const
{
    m_world.Render();
    Sprite* sprite = m_sprite_manager->GetSprite("blocks", "dirt");
    sprite->Render();
}

void GameScene::Update() { }