#include "core/Sprite.h"

Sprite::Sprite(Texture2D* texture, float x, float y, float width, float height)
    : m_texture(texture)
    , m_sprite_x(x)
    , m_sprite_y(y)
    , m_sprite_height(height)
    , m_sprite_width(width)
{ }

void Sprite::Render(float x, float y, float scale, float rotation, Color tint) const
{
    Rectangle source = {m_sprite_x, m_sprite_y, m_sprite_width, m_sprite_height};
    Rectangle dest = {x, y, m_sprite_width * scale, m_sprite_height * scale};
    DrawTexturePro(*m_texture, source, dest, {0, 0}, rotation, tint);
}

float Sprite::GetWidth() const { return m_sprite_width; }

float Sprite::GetHeight() const { return m_sprite_height; }