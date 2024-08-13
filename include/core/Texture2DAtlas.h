#ifndef URLAND_TEXTURE_2D_ATLAS_H
#define URLAND_TEXTURE_2D_ATLAS_H

#include <raylib.h>

class Texture2DAtlas
{
public:
    Texture2DAtlas() = default;
    Texture2DAtlas(const char* path, float tilesize);
    Texture2D& GetTexture() const;
    int GetTileSize() const;
    void DrawSprite(int index, float x, float y, Color tint = {255, 255, 255, 255}, float scale = 1.0f) const;

private:
    Texture2D m_texture;
    float m_tilesize;
    int m_columns;
};

#endif // URLAND_TEXTURE_2D_ATLAS_H