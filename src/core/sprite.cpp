#include "core/sprite.h"

Sprite::Sprite(Texture2D* texture, float x, float y, float width, float height)
    : mTexture(texture)
    , mSpriteX(x)
    , mSpriteY(y)
    , mSpriteHeight(height)
    , mSpriteWidth(width)
{
}

void Sprite::Render(float x, float y, float scale, float rotation, Color tint) const
{
    Rectangle source = {mSpriteX, mSpriteY, mSpriteWidth, mSpriteHeight};
    Rectangle dest = {x, y, mSpriteWidth * scale, mSpriteHeight * scale};
    DrawTexturePro(*mTexture, source, dest, {0, 0}, rotation, tint);
}

float Sprite::GetWidth() const { return mSpriteWidth; }

float Sprite::GetHeight() const { return mSpriteHeight; }