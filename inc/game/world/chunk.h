#ifndef CHUNK_H
#define CHUNK_H

#include <memory>
#include <array>
#include <unordered_set>
#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "game/world/Block.h"
#include "core/Constants.h"

class Chunk
{
public:
    Chunk() = default;
    ~Chunk();

    void Init(unsigned int index, Texture2D& atlas, Material& material);
    void Load();
    void Render() const;
    void Update();
    Block& BlockAt(int blockIndex) { return mBlocks[blockIndex]; }
    void PlaceBlock(int blockIndex, Block& block);
    void MineBlock(int blockIndex, float damage);
    Vector2 GetPosition() const { return mPosition; }
    Vector2 GetPositionPixels() const { return Vector2Scale(mPosition, CHUNK_SIZE_PIXELS); }
    const std::vector<Rectangle>& GetCollisionRects() const { return mCollisionRects; }
    Rectangle GetAreaPixels() const
    {
        Vector2 pos = GetPositionPixels();
        return {pos.x, pos.y, CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS};
    }
    Rectangle GetAreaBlocks() const
    {
        Rectangle pos = GetAreaPixels();
        pos.x /= BLOCK_SIZE_PIXELS;
        pos.y /= BLOCK_SIZE_PIXELS;
        pos.width /= BLOCK_SIZE_PIXELS;
        pos.height /= BLOCK_SIZE_PIXELS;
        return pos;
    }

    std::array<Block, CHUNK_LENGTH_BLOCKS>& GetBlocks() { return mBlocks; };
    void SetMeshIsDirty() { mMeshIsDirty = true; }
    void SetCollisionIsDirty() { mCollisionIsDirty = true; }
    void SetBlocksAreDirty() { mBlocksAreDirty = true; }

private:
    void mGenerateMesh();
    void mUpdateTexture();
    void mGenerateCollisionRects();
    void mBlockTexUpdate(std::array<float, CHUNK_MESH_VERTEX_COUNT * 2>& texcoords, int& vertexIndex, int blockIndex);

    std::array<Block, CHUNK_LENGTH_BLOCKS> mBlocks;
    std::vector<Rectangle> mCollisionRects;
    Vector2 mPosition = {0, 0};
    Mesh mMesh;
    Matrix mMatrix;
    Material* mMaterial;
    Texture2D* mAtlas;
    std::unordered_set<int> mDamagedBlocks = {};
    float mTextureUnit = 0.0f;
    bool mMeshIsDirty = true;
    bool mCollisionIsDirty = true;
    bool mBlocksAreDirty = true;
};

#endif // CHUNK_H