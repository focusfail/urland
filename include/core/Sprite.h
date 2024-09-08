#pragma once

#include <raylib.h>
#include <memory>

class Sprite
{
public:
    Sprite() = default;
    Sprite(Texture* texture, float x, float y, float width, float height);
    void Render(float x = 0, float y = 0, float scale = 1.0f, float rotation = 0.0f, Color tint = WHITE) const;
    float GetWidth() const;
    float GetHeight() const;

private:
    Texture2D* m_texture;
    float m_sprite_x = 0;
    float m_sprite_y = 0;
    float m_sprite_width = 0;
    float m_sprite_height = 0;
};