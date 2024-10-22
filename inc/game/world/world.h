#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <array>

#include "raylib.h"

#include "game/world/chunk.h"

class World
{
public:
    World() = default;
    ~World();

    void Init(Texture2D& atlas);
    void Render(Camera2D& camera) const;
    void RenderDebugGrid(bool chunkGrid = true, bool blockGrid = true);
    void Update(Camera2D& camera);

private:
    bool mShouldRenderChunk(const Chunk& chunk, Camera2D& camera) const;

    std::vector<Chunk> mChunks;
    std::vector<int> mActiveChunkIndices = {};
    std::vector<int> mLoadedChunks = {};
    Texture2D* mAtlas;
    Material mBlockTextureMaterial;
};

#endif // WORLD_H