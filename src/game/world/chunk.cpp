#include "game/world/chunk.h"

#include <format>

#include "raymath.h"

#include "core/conversions.h"

Chunk::~Chunk()
{
    SetTraceLogLevel(LOG_WARNING);
    UnloadMesh(mMesh);
    UnloadMaterial(*mMaterial);
    SetTraceLogLevel(LOG_INFO);
}

void Chunk::Render() const
{
    if (mAtlas == nullptr) {
        TraceLog(LOG_WARNING, "Tried rendering uninitialized chunk.");
        return;
    }
    DrawMesh(mMesh, *mMaterial, mMatrix);
}

void Chunk::Init(unsigned int index, Texture2D& atlas, Material& material)
{
    mAtlas = &atlas;
    mPosition = {(float)(index % TERRAIN_WIDTH_CHUNKS), (float)(index / TERRAIN_WIDTH_CHUNKS)};
    mMatrix = MatrixTranslate(mPosition.x * CHUNK_SIZE_PIXELS, mPosition.y * CHUNK_SIZE_PIXELS, 0);
    mMaterial = &material;
}

void Chunk::Load() { mGenerateMesh(); }

void Chunk::mGenerateMesh()
{
    const int vertexCount = CHUNK_LENGTH_BLOCKS * 4;
    const int indexCount = CHUNK_LENGTH_BLOCKS * 6;
    const int textureUnit = BLOCK_SIZE_PIXELS / mAtlas->width;

    std::array<float, vertexCount * 3> vertices;
    std::array<float, vertexCount * 2> texcoords;
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

        float texX = (mBlocks[blockIndex].id % (mAtlas->width / BLOCK_SIZE_PIXELS)) * textureUnit;
        float texY = (mBlocks[blockIndex].id / (mAtlas->width / BLOCK_SIZE_PIXELS)) * textureUnit;
        texcoords[vertexIndex * 2 + 0] = texX;
        texcoords[vertexIndex * 2 + 1] = texY;
        texcoords[vertexIndex * 2 + 2] = texX + textureUnit;
        texcoords[vertexIndex * 2 + 3] = texY;
        texcoords[vertexIndex * 2 + 4] = texX + textureUnit;
        texcoords[vertexIndex * 2 + 5] = texY + textureUnit;
        texcoords[vertexIndex * 2 + 6] = texX;
        texcoords[vertexIndex * 2 + 7] = texY + textureUnit;

        indices[indexIndex++] = vertexIndex;
        indices[indexIndex++] = vertexIndex + 1;
        indices[indexIndex++] = vertexIndex + 2;
        indices[indexIndex++] = vertexIndex;
        indices[indexIndex++] = vertexIndex + 2;
        indices[indexIndex++] = vertexIndex + 3;

        vertexIndex += 4;
    }

    mMesh = {0};
    mMesh.vertexCount = vertexCount;
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