#include "game/world/world.h"

#include <iostream>

#include "core/conversions.h"

World::~World() { UnloadMaterial(mBlockTextureMaterial); }

void World::Init(Texture2D& atlas)
{
    mAtlas = &atlas;
    mBlockTextureMaterial = LoadMaterialDefault();
    mBlockTextureMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = atlas;
    mChunks.resize(TERRAIN_LENGTH_CHUNKS);

    for (int chunkIndex = 0; chunkIndex < TERRAIN_LENGTH_CHUNKS; chunkIndex++) {
        Chunk& chunk = mChunks[chunkIndex];
        chunk.Init(chunkIndex, *mAtlas, mBlockTextureMaterial);
        chunk.Load();
    }
}

void World::Render(Camera2D& camera) const
{
    for (int activeChunkIndex : mActiveChunkIndices) {
        const Chunk& chunk = mChunks[activeChunkIndex];
        if (mShouldRenderChunk(chunk, camera))
            chunk.Render();
        else {
            std::cout << "Skipped outside-of-bounds chunk.\n";
        }
    }
}

bool World::mShouldRenderChunk(const Chunk& chunk, Camera2D& camera) const
{
    Rectangle chunkArea = chunk.GetAreaPixels();
    Vector2 screenTopLeft = GetScreenToWorld2D(Vector2 {0.0f, 0.0f}, camera);
    Vector2 screenBottomRight = GetScreenToWorld2D(Vector2 {(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);
    Rectangle frustum = {screenTopLeft.x, screenTopLeft.y, screenBottomRight.x, screenBottomRight.y};
    return CheckCollisionRecs(chunkArea, frustum);
}

void World::RenderDebugGrid(bool chunkGrid, bool blockGrid)
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

void World::Update(Camera2D& camera)
{
    Vector2 start = WorldToChunkPosition(camera.target);
    mActiveChunkIndices.clear();
    for (int y = start.y - RENDER_SQUARE_RADIUS; y <= start.y + RENDER_SQUARE_RADIUS; y++) {
        if (y < 0 || y >= TERRAIN_HEIGHT_CHUNKS) continue;

        for (int x = start.x - RENDER_SQUARE_RADIUS; x <= start.x + RENDER_SQUARE_RADIUS; x++) {
            if (x < 0 || x >= TERRAIN_WIDTH_CHUNKS) continue;
            int chunkIndex = ChunkPositionToIndex(Vector2 {(float)x, (float)y});
            mActiveChunkIndices.push_back(chunkIndex);
        }
    }
};