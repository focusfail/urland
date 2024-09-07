#pragma once

class GameState;

class Scene
{
public:
    Scene(GameState* game_state)
        : _game_state(game_state) {};
    virtual ~Scene() = default;
    virtual void Update() = 0;
    virtual void Render() const = 0;

protected:
    GameState* _game_state;
};