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
    Texture2D* mTexture;
    float mSpriteX = 0;
    float mSpriteY = 0;
    float mSpriteWidth = 0;
    float mSpriteHeight = 0;
};