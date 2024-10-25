#include "game/world/world.h"

#include <iostream>
#include <chrono>

#include "rlgl.h"
#include "core/conversions.h"

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
    // rlDisableBackfaceCulling();
    for (int activeChunkIndex : mActiveChunkIndices) {
        const Chunk& chunk = mChunks[activeChunkIndex];
        if (mShouldRenderChunk(chunk, camera)) { chunk.Render(); }
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

void World::RenderDebugGrid(bool chunkGrid, bool blockGrid) const
{
    if (!chunkGrid && !blockGrid) return;

    for (int activeChunkIndex : mActiveChunkIndices) {
        const Chunk& chunk = mChunks[activeChunkIndex];
        Vector2 chunkPos = chunk.GetPosition();
        chunkPos.x *= CHUNK_SIZE_PIXELS;
        chunkPos.y *= CHUNK_SIZE_PIXELS;

        if (blockGrid) {
            // use chunkGrid bool to determine if the border should be drawn

            for (int i = (int)chunkGrid; i <= CHUNK_SIZE_BLOCKS; i++) {
                DrawLine(BLOCK_SIZE_PIXELS * i + chunkPos.x, chunkPos.y, BLOCK_SIZE_PIXELS * i + chunkPos.x,
                         CHUNK_SIZE_PIXELS + chunkPos.y, WHITE);
                DrawLine(chunkPos.x, BLOCK_SIZE_PIXELS * i + chunkPos.y, CHUNK_SIZE_PIXELS + chunkPos.x,
                         BLOCK_SIZE_PIXELS * i + chunkPos.y, WHITE);
            }
        }
        if (chunkGrid) {
            DrawRectangleLinesEx(Rectangle {chunkPos.x, chunkPos.y, CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS}, 3.0f, RED);
        }
    }
}

void World::Update(Camera2D& camera, int renderDistance)
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
    for (int y = originChunkPos.y - renderDistance; y <= originChunkPos.y + renderDistance; y++) {
        if (y < 0 || y >= TERRAIN_HEIGHT_CHUNKS) continue;

        for (int x = originChunkPos.x - renderDistance; x <= originChunkPos.x + renderDistance; x++) {
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