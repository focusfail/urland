#include "core/Texture2DAtlas.h"

#include <raymath.h>

#include <cassert>

Texture2DAtlas::Texture2DAtlas(const char* path, float tilesize)
    : m_texture(LoadTexture(path))
    , m_tilesize(tilesize)
{
    m_columns = static_cast<int>(m_texture.width / m_tilesize);
}

void Texture2DAtlas::DrawSprite(int index, float x, float y, float scale) const
{
    int ix = static_cast<int>(fmod(index, m_columns));
    int iy = static_cast<int>(index / m_columns);

    Rectangle source = {ix * m_tilesize, iy * m_tilesize, m_tilesize, m_tilesize};
    Rectangle dest = {x, y, m_tilesize * scale, m_tilesize * scale};

    DrawTexturePro(m_texture, source, dest, Vector2Zero(), 0.0f, WHITE);
}