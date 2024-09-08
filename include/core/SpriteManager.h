#pragma once

#include "core/Sprite.h"

#include <raylib.h>
#include <memory>
#include <string>
#include <unordered_map>

using std::string, std::unordered_map, std::make_pair;

class SpriteManager
{
public:
    SpriteManager();
    ~SpriteManager();
    void AddTexture(const string& name, const string& path);
    void AddSprite(const string& texture_name, const string& sprite_name, float start_x, float start_y, float width,
                   float height);
    Texture2D* GetTexture(const string& texture_name);
    Sprite* GetSprite(const string& texture_name, const string& sprite_name);

private:
    unordered_map<string, Texture2D> m_textures;
    unordered_map<string, Sprite> m_sprites;
};