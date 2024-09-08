#pragma once

class GameState;

class Scene
{
public:
    Scene(GameState* game_state)
        : m_game_state(game_state) {};
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() const = 0;

protected:
    GameState* m_game_state;
};