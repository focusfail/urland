#include "game/world/World.h"

#include <iostream>
#include <cassert>
#include <chrono>

#include "rlgl.h"
#include "core/Conversions.h"
#include "core/Globals.h"

#include "game/world/Block.h"
#include "game/BlockInfo.h"

World::~World() { UnloadMaterial(mBlockTextureMaterial); }

void World::Init(Texture2D& atlas)
{
    auto timeA = std::chrono::high_resolution_clock::now();
    TraceLog(LOG_INFO, "WORLDGEN: Initializing world.");
    mAtlas = &atlas;
    mBlockTextureMaterial = LoadMaterialDefault();
    SetMaterialTexture(&mBlockTextureMaterial, MATERIAL_MAP_DIFFUSE, atlas);
    mChunks.resize(TERRAIN_LENGTH_CHUNKS);
    mGenerator.GenerateNoise();

    for (int chunkIndex = 0; chunkIndex < TERRAIN_LENGTH_CHUNKS; chunkIndex++) {
        Chunk& chunk = mChunks[chunkIndex];
        chunk.Init(chunkIndex, *mAtlas, mBlockTextureMaterial);
        chunk.Load();
        mGenerator.ApplyNoise(chunk);
        chunk.SetCollisionIsDirty();
        chunk.SetMeshIsDirty();
    }

    auto timeB = std::chrono::high_resolution_clock::now();
    auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA);
    TraceLog(LOG_INFO, std::format("WORLDGEN: Generated world in: {} ms", timeTaken.count()).c_str());

    assert(!BLOCK_INFO[0 /*air*/].isSolid);
    assert(BLOCK_INFO[1 /*dirt*/].isSolid);
}

void World::Generate(GenerationOptions opts)
{
    auto timeA = std::chrono::high_resolution_clock::now();
    mGenerator.GenerateNoise(opts);

    for (int chunkIndex = 0; chunkIndex < TERRAIN_LENGTH_CHUNKS; chunkIndex++) {
        Chunk& chunk = mChunks[chunkIndex];
        mGenerator.ApplyNoise(chunk);
        chunk.SetCollisionIsDirty();
        chunk.SetMeshIsDirty();
    }
    ForceUpdate();
    auto timeB = std::chrono::high_resolution_clock::now();
    auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA);
    TraceLog(LOG_INFO, std::format("WORLDGEN: Generated world in: {} ms", timeTaken.count()).c_str());
}

void World::Render(const Camera2D& camera) const
{
    // Draw chunks
    for (int activeChunkIndex : mActiveChunkIndices) {
        const Chunk& chunk = mChunks[activeChunkIndex];
        if (mShouldRenderChunk(chunk, camera)) { chunk.Render(); }
    }

    // Draw debug grids
    if (!DBG_DRAW_BLOCK_BD && !DBG_DRAW_CHUNK_BD) return;

    for (int activeChunkIndex : mActiveChunkIndices) {
        const Chunk& chunk = mChunks[activeChunkIndex];
        Vector2 chunkPos = chunk.GetPosition();
        chunkPos.x *= CHUNK_SIZE_PIXELS;
        chunkPos.y *= CHUNK_SIZE_PIXELS;

        if (DBG_DRAW_BLOCK_BD) {
            // use chunkGrid bool to determine if the border should be drawn

            for (int i = (int)DBG_DRAW_CHUNK_BD; i <= CHUNK_SIZE_BLOCKS; i++) {
                DrawLine(BLOCK_SIZE_PIXELS * i + chunkPos.x, chunkPos.y, BLOCK_SIZE_PIXELS * i + chunkPos.x,
                         CHUNK_SIZE_PIXELS + chunkPos.y, WHITE);
                DrawLine(chunkPos.x, BLOCK_SIZE_PIXELS * i + chunkPos.y, CHUNK_SIZE_PIXELS + chunkPos.x,
                         BLOCK_SIZE_PIXELS * i + chunkPos.y, WHITE);
            }
        }
        if (DBG_DRAW_CHUNK_BD) {
            DrawRectangleLinesEx(Rectangle {chunkPos.x, chunkPos.y, CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS}, 2.0f, RED);
        }
    }
}

bool World::mShouldRenderChunk(const Chunk& chunk, const Camera2D& camera) const
{
    Rectangle chunkArea = chunk.GetAreaPixels();
    Vector2 screenTopLeft = GetScreenToWorld2D(Vector2 {0.0f, 0.0f}, camera);
    Vector2 screenBottomRight = GetScreenToWorld2D(Vector2 {(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);
    Rectangle frustum = {screenTopLeft.x, screenTopLeft.y, screenBottomRight.x - screenTopLeft.x,
                         screenBottomRight.y - screenTopLeft.y};

    return CheckCollisionRecs(chunkArea, frustum);
}

void World::Update(Camera2D& camera)
{
    Vector2 originChunkPos = WorldToChunkPosition(camera.target);

    // Return and only update forced chunks if nothing changed
    if (originChunkPos.x == mLastOriginChunkPos.x && originChunkPos.y == mLastOriginChunkPos.y && !mForceUpdate) {
        for (int chunkIndex : mNextForcedUpdates) {
            Chunk& chunk = mChunks[chunkIndex];
            chunk.Update();
        }
        mNextForcedUpdates.clear();
        return;
    }

    mActiveChunkIndices.clear();
    for (int y = originChunkPos.y - RENDER_DISTANCE; y <= originChunkPos.y + RENDER_DISTANCE; y++) {
        if (y < 0 || y >= TERRAIN_HEIGHT_CHUNKS) continue;

        for (int x = originChunkPos.x - RENDER_DISTANCE; x <= originChunkPos.x + RENDER_DISTANCE; x++) {
            if (x < 0 || x >= TERRAIN_WIDTH_CHUNKS) continue;
            int chunkIndex = ChunkPositionToIndex(Vector2 {(float)x, (float)y});
            Chunk& chunk = mChunks[chunkIndex];
            chunk.Update();
            mActiveChunkIndices.push_back(chunkIndex);
        }
    }
    mNextForcedUpdates.clear();
    mLastOriginChunkPos = originChunkPos;
};

bool World::PlaceBlock(Vector2 position, Block& block)
{
    // Return if the position is not within the world boundaries
    if (!CheckCollisionPointRec(position, WORLD_RECT)) return false;

    Vector2 chunkP = WorldToChunkPosition(position);
    int chunkI = ChunkPositionToIndex(chunkP);
    Chunk& chunk = mChunks[chunkI];
    int blockIndex = WorldToBlockIndex(position);
    chunk.PlaceBlock(blockIndex, block);
    SetForceChunkUpdate(chunkI);

    return true;
}