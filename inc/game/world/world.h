#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <unordered_set>
#include <array>

#include "raylib.h"

#include "core/Constants.h"
#include "game/world/Chunk.h"
#include "game/world/Generator.h"

class World
{
public:
    World() = default;
    ~World();

    void Init(Texture2D& atlas);
    void Generate(GenerationOptions opts = {});
    void Render(const Camera2D& camera) const;
    void Update(Camera2D& camera);
    bool PlaceBlock(Vector2 position, Block& block);
    void SetForceChunkUpdate(int chunkIndex) { mNextForcedUpdates.insert(chunkIndex); }
    Chunk& GetChunk(int chunkIndex) { return mChunks.at(chunkIndex); }
    void ForceUpdate() { mForceUpdate = true; }

private:
    bool mShouldRenderChunk(const Chunk& chunk, const Camera2D& camera) const;

    std::vector<Chunk> mChunks;
    std::vector<int> mActiveChunkIndices = {};
    std::vector<int> mLoadedChunks = {};
    Generator mGenerator;
    Texture2D* mAtlas;
    Material mBlockTextureMaterial;
    Vector2 mLastOriginChunkPos = {0, 0};
    std::unordered_set<int> mNextForcedUpdates = {};
    bool mForceUpdate = false;
};

#endif // WORLD_H