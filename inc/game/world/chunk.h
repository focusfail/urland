#ifndef CHUNK_H
#define CHUNK_H

#include <memory>
#include <array>

#include "raylib.h"
#include "raymath.h"

#include "game/world/block.h"
#include "core/constants.h"

class Chunk
{
public:
    Chunk() = default;
    ~Chunk();

    void Init(unsigned int index, Texture2D& atlas, Material& material);
    void Load();
    void Render() const;
    Vector2 GetPosition() const { return mPosition; }
    Vector2 GetPositionPixels() const { return Vector2Scale(mPosition, CHUNK_SIZE_PIXELS); }
    Rectangle GetAreaPixels() const
    {
        Vector2 pos = GetPositionPixels();
        return {pos.x, pos.y, CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS};
    }

private:
    void mGenerateMesh();

    std::array<Block, CHUNK_LENGTH_BLOCKS> mBlocks;
    Vector2 mPosition = {0, 0};
    Mesh mMesh;
    Matrix mMatrix;
    Material* mMaterial;
    Texture2D* mAtlas;
};

#endif // CHUNK_H