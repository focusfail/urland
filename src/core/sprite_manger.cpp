#include "core/sprite_manager.h"

#include <rlgl.h>
#include <format>

SpriteManager::SpriteManager()
{
    mTextures = unordered_map<string, Texture2D>();
    mSprites = unordered_map<string, Sprite>();
}

SpriteManager::~SpriteManager()
{
    for (auto& pair : mTextures) { UnloadTexture(pair.second); }
}

void SpriteManager::AddTexture(const std::string& name, const std::string& path)
{
    Texture2D tex = LoadTexture(path.c_str());
    SetTextureFilter(tex, RL_TEXTURE_FILTER_NEAREST);
    SetTextureWrap(tex, TEXTURE_WRAP_CLAMP);
    mTextures.emplace(make_pair(name, tex));
}

void SpriteManager::AddSprite(const string& textureName, const string& spriteName, float startX, float startY,
                              float width, float height)
{
    string id = std::format("{}/{}", textureName, spriteName);

    Texture2D* tex_ptr = &mTextures.at(textureName);
    mSprites.emplace(make_pair(id, Sprite(tex_ptr, startX, startY, width, height)));
    TraceLog(LOG_INFO, TextFormat("SpriteManager: Added sprite \"%s\"", id.c_str()));
}

Sprite* SpriteManager::GetSprite(const string& textureName, const string& spriteName)
{
    string id = std::format("{}/{}", textureName, spriteName);
    return &mSprites.at(id);
}

Texture2D* SpriteManager::GetTexture(const string& textureName) { return &mTextures.at(textureName); }