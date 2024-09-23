#include "core/SpriteManager.h"

#include <rlgl.h>
#include <format>

SpriteManager::SpriteManager()
{
    m_textures = unordered_map<string, Texture2D>();
    m_sprites = unordered_map<string, Sprite>();
}

SpriteManager::~SpriteManager()
{
    for (auto& pair : m_textures) { UnloadTexture(pair.second); }
}

void SpriteManager::AddTexture(const std::string& name, const std::string& path)
{
    Texture2D tex = LoadTexture(path.c_str());
    SetTextureFilter(tex, RL_TEXTURE_FILTER_POINT);
    // SetTextureWrap(tex, TEXTURE_WRAP_CLAMP);
    m_textures.emplace(make_pair(name, tex));
}

void SpriteManager::AddSprite(const string& texture_name, const string& sprite_name, float start_x, float start_y,
                              float width, float height)
{
    string id = std::format("{}/{}", texture_name, sprite_name);

    Texture2D* tex_ptr = &m_textures.at(texture_name);
    m_sprites.emplace(make_pair(id, Sprite(tex_ptr, start_x, start_y, width, height)));
    TraceLog(LOG_INFO, TextFormat("SpriteManager: Added sprite \"%s\"", id.c_str()));
}

Sprite* SpriteManager::GetSprite(const string& texture_name, const string& sprite_name)
{
    string id = std::format("{}/{}", texture_name, sprite_name);
    return &m_sprites.at(id);
}

Texture2D* SpriteManager::GetTexture(const string& texture_name) { return &m_textures.at(texture_name); }