#include "game/world/Chunk.h"

#include <format>
#include <vector>
#include <iostream>

#include "raymath.h"
#include "rlgl.h"

#include "core/Conversions.h"
#include "core/Globals.h"
#include "game/BlockInfo.h"

Chunk::~Chunk()
{
    SetTraceLogLevel(LOG_WARNING);
    UnloadMesh(mMesh);
    UnloadMaterial(*mMaterial);
    SetTraceLogLevel(LOG_INFO);
}

void Chunk::Update()
{
    if (mMeshIsDirty) mUpdateTexture();
    if (mCollisionIsDirty) mGenerateCollisionRects();
}

void Chunk::Render() const
{
    if (mAtlas == nullptr) return;
    DrawMesh(mMesh, *mMaterial, mMatrix);
    if (DBG_DRAW_COL_REC)
        for (const Rectangle& rect : mCollisionRects) DrawRectangleLinesEx(rect, 1.0f, PURPLE);
}

void Chunk::Init(unsigned int index, Texture2D& atlas, Material& material)
{
    mAtlas = &atlas;
    mTextureUnit = (float)BLOCK_SIZE_PIXELS / (float)mAtlas->width;
    mPosition = {(float)(index % TERRAIN_WIDTH_CHUNKS), (float)(index / TERRAIN_WIDTH_CHUNKS)};
    mMatrix = MatrixTranslate(mPosition.x * CHUNK_SIZE_PIXELS, mPosition.y * CHUNK_SIZE_PIXELS, 0);
    mMaterial = &material;
}

void Chunk::Load()
{
    mGenerateMesh();
    mGenerateCollisionRects();
}

void Chunk::PlaceBlock(int blockIndex, Block& block)
{
    if (blockIndex > CHUNK_LENGTH_BLOCKS || blockIndex < 0) return;
    Block& previousBlock = mBlocks[blockIndex];

    if (previousBlock.id == block.id)
        return;
    else if (BLOCK_INFO[previousBlock.id].isSolid != BLOCK_INFO[block.id].isSolid) {
        mCollisionIsDirty = true;
    }

    mMeshIsDirty = true;
    previousBlock = block;
}

void Chunk::mUpdateTexture()
{
    std::array<float, CHUNK_MESH_VERTEX_COUNT * 2> texcoords;

    int vertexIndex = 0;
    for (int blockIndex = 0; blockIndex < CHUNK_LENGTH_BLOCKS; blockIndex++) {
        mBlockTexUpdate(texcoords, vertexIndex, blockIndex);
        vertexIndex += 4;
    }

    // Update only the texture coordinates in GPU memory
    UpdateMeshBuffer(mMesh, 1, texcoords.data(), texcoords.size() * sizeof(float), 0);
    mMeshIsDirty = false;
}

void Chunk::mBlockTexUpdate(std::array<float, CHUNK_MESH_VERTEX_COUNT * 2>& texcoords, int& vertexIndex, int blockIndex)
{
    float padding = 0.001f;
    const Block& block = mBlocks[blockIndex];
    // Get the correct index for the specific block variant
    int texID = BLOCK_INFO[block.id].textureID + block.variant - 1;
    float texX = (texID % (mAtlas->width / BLOCK_SIZE_PIXELS)) * mTextureUnit;
    float texY = (texID / (mAtlas->width / BLOCK_SIZE_PIXELS)) * mTextureUnit;

    float texMaxX = texX + mTextureUnit - padding;
    float texMaxY = texY + mTextureUnit - padding;

    texcoords[vertexIndex * 2 + 0] = texX + padding;
    texcoords[vertexIndex * 2 + 1] = texY + padding;
    texcoords[vertexIndex * 2 + 2] = texMaxX;
    texcoords[vertexIndex * 2 + 3] = texY + padding;
    texcoords[vertexIndex * 2 + 4] = texMaxX;
    texcoords[vertexIndex * 2 + 5] = texMaxY;
    texcoords[vertexIndex * 2 + 6] = texX + padding;
    texcoords[vertexIndex * 2 + 7] = texMaxY;
}

void Chunk::mGenerateMesh()
{
    //! maybe use GenMeshPlane() to generate chunk mesh
    const int indexCount = CHUNK_LENGTH_BLOCKS * 6;

    std::array<float, CHUNK_MESH_VERTEX_COUNT * 3> vertices;
    std::array<float, CHUNK_MESH_VERTEX_COUNT * 2> texcoords;
    std::array<unsigned short, indexCount> indices;

    int vertexIndex = 0;
    int indexIndex = 0;

    for (int blockIndex = 0; blockIndex < CHUNK_LENGTH_BLOCKS; blockIndex++) {
        Vector2 blockPos = BlockIndexToPosition(blockIndex);
        Vector2 blockPosPixels = Vector2Scale(blockPos, BLOCK_SIZE_PIXELS);

        vertices[vertexIndex * 3 + 0] = blockPosPixels.x;
        vertices[vertexIndex * 3 + 1] = blockPosPixels.y;
        vertices[vertexIndex * 3 + 2] = 0;

        vertices[vertexIndex * 3 + 3] = blockPosPixels.x + BLOCK_SIZE_PIXELS;
        vertices[vertexIndex * 3 + 4] = blockPosPixels.y;
        vertices[vertexIndex * 3 + 5] = 0;

        vertices[vertexIndex * 3 + 6] = blockPosPixels.x + BLOCK_SIZE_PIXELS;
        vertices[vertexIndex * 3 + 7] = blockPosPixels.y + BLOCK_SIZE_PIXELS;
        vertices[vertexIndex * 3 + 8] = 0;

        vertices[vertexIndex * 3 + 9] = blockPosPixels.x;
        vertices[vertexIndex * 3 + 10] = blockPosPixels.y + BLOCK_SIZE_PIXELS;
        vertices[vertexIndex * 3 + 11] = 0;

        mBlockTexUpdate(texcoords, vertexIndex, blockIndex);

        indices[indexIndex++] = vertexIndex;
        indices[indexIndex++] = vertexIndex + 3;
        indices[indexIndex++] = vertexIndex + 2;

        indices[indexIndex++] = vertexIndex;
        indices[indexIndex++] = vertexIndex + 2;
        indices[indexIndex++] = vertexIndex + 1;

        vertexIndex += 4;
    }

    mMesh = {0};
    mMesh.vertexCount = CHUNK_MESH_VERTEX_COUNT;
    mMesh.triangleCount = indexCount / 3;

    mMesh.vertices = (float*)MemAlloc(vertices.size() * sizeof(float));
    mMesh.texcoords = (float*)MemAlloc(texcoords.size() * sizeof(float));
    mMesh.indices = (unsigned short*)MemAlloc(indices.size() * sizeof(unsigned short));

    memcpy(mMesh.vertices, vertices.data(), vertices.size() * sizeof(float));
    memcpy(mMesh.texcoords, texcoords.data(), texcoords.size() * sizeof(float));
    memcpy(mMesh.indices, indices.data(), indices.size() * sizeof(unsigned short));

    SetTraceLogLevel(LOG_WARNING);
    UploadMesh(&mMesh, false);
    SetTraceLogLevel(LOG_INFO);
}

void Chunk::mGenerateCollisionRects()
{
    mCollisionRects.clear();

    Vector2 chunkPos = GetPositionPixels();
    bool visited[CHUNK_SIZE_BLOCKS][CHUNK_SIZE_BLOCKS] = {false};

    for (int y = 0; y < CHUNK_SIZE_BLOCKS; ++y) {
        for (int x = 0; x < CHUNK_SIZE_BLOCKS; ++x) {
            if (!visited[y][x]) {
                int block_index = y * CHUNK_SIZE_BLOCKS + x;
                const Block& block = mBlocks[block_index];

                if (BLOCK_INFO[block.id].isSolid) {
                    int width = 1;
                    int height = 1;

                    // Expand horizontally
                    while (x + width < CHUNK_SIZE_BLOCKS && !visited[y][x + width] &&
                           BLOCK_INFO[mBlocks[y * CHUNK_SIZE_BLOCKS + (x + width)].id].isSolid) {
                        ++width;
                    }

                    // Expand vertically
                    bool can_expand_vertically = true;
                    while (can_expand_vertically && y + height < CHUNK_SIZE_BLOCKS) {
                        for (int i = 0; i < width; ++i) {
                            if (visited[y + height][x + i] ||
                                !BLOCK_INFO[mBlocks[(y + height) * CHUNK_SIZE_BLOCKS + (x + i)].id].isSolid) {
                                can_expand_vertically = false;
                                break;
                            }
                        }
                        if (can_expand_vertically) ++height;
                    }

                    // Mark all blocks in this rectangle as visited
                    for (int j = 0; j < height; ++j) {
                        for (int i = 0; i < width; ++i) { visited[y + j][x + i] = true; }
                    }

                    // Add the bounding box
                    mCollisionRects.emplace_back(x * BLOCK_SIZE_PIXELS + chunkPos.x, y * BLOCK_SIZE_PIXELS + chunkPos.y,
                                                 width * BLOCK_SIZE_PIXELS, height * BLOCK_SIZE_PIXELS);
                }
            }
        }
    }

    // std::cout << "chunk has: " << mCollisionRects.size() << "rects\n";
    mCollisionIsDirty = false;
}