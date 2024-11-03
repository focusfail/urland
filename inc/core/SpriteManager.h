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
    void AddSprite(const string& textureName, const string& spriteName, float startX, float startY, float width,
                   float height);
    Texture2D* GetTexture(const string& textureName);
    Sprite* GetSprite(const string& textureName, const string& spriteName);

private:
    unordered_map<string, Texture2D> mTextures;
    unordered_map<string, Sprite> mSprites;
};