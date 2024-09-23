#include "core/Chunk.h"
#include "core/Constants.h"
#include "core/Convertions.h"

#include <raylib.h>
#include <rlgl.h>
#include <iostream>

Chunk::~Chunk() { }

void Chunk::Init()
{
    Block block;
    m_blocks.fill(block);
}

const Block& Chunk::GetBlock(int block_index) const { return m_blocks.at(block_index); }

void Chunk::Render(Texture2D* atlas) const
{
    float columns = atlas->width / BLOCK_SIZE_PIXELS;

    for (int block_i = 0; block_i < CHUNK_LENGTH_BLOCKS; block_i++) {
        const Block& block = m_blocks.at(block_i);

        auto [x, y] = BlockIndexToPositionInChunk(block_i);
        auto [cx, cy] = ChunkIndexToPosition(m_index);
        x = BlocksAsPixels(ChunksAsBlocks(cx) + x);
        y = BlocksAsPixels(ChunksAsBlocks(cy) + y);

        const int tex_idx = block.texture_id;
        const int ix = static_cast<int>(fmod(tex_idx, columns));
        const int iy = static_cast<int>(tex_idx / columns);

        Rectangle source(ix * BLOCK_SIZE_PIXELS, iy * BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS);
        Rectangle dest(x, y, BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS);

        DrawTexturePro(*atlas, source, dest, Vector2Zero(), 0.0f, WHITE);
    }

    // for (auto& bb : m_bounding_boxes) { DrawRectangleLinesEx(bb, 1.0f, RED); }
}

void Chunk::Update()
{
    if (!m_dirty) return;

    std::cout << "[UPDATE] Chunk: " << m_index << "\n";

    m_GenerateBoundingBoxes();
    m_dirty = false;
}

void Chunk::SetIndex(ChunkIndex index) { m_index = index; }

void Chunk::m_GenerateBoundingBoxes()
{
    m_bounding_boxes.clear();
    auto [chunk_x, chunk_y] = ChunkIndexToPosition(m_index);
    bool visited[CHUNK_SIZE_BLOCKS][CHUNK_SIZE_BLOCKS] = {false};

    for (int y = 0; y < CHUNK_SIZE_BLOCKS; ++y) {
        for (int x = 0; x < CHUNK_SIZE_BLOCKS; ++x) {
            if (!visited[y][x]) {
                int block_index = y * CHUNK_SIZE_BLOCKS + x;
                const Block& block = m_blocks.at(block_index);

                if (block.is_solid) {
                    int width = 1;
                    int height = 1;

                    // Expand horizontally
                    while (x + width < CHUNK_SIZE_BLOCKS && !visited[y][x + width] &&
                           m_blocks.at(y * CHUNK_SIZE_BLOCKS + (x + width)).is_solid) {
                        ++width;
                    }

                    // Expand vertically
                    bool can_expand_vertically = true;
                    while (can_expand_vertically && y + height < CHUNK_SIZE_BLOCKS) {
                        for (int i = 0; i < width; ++i) {
                            if (visited[y + height][x + i] ||
                                !m_blocks.at((y + height) * CHUNK_SIZE_BLOCKS + (x + i)).is_solid) {
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
                    m_bounding_boxes.emplace_back(x * BLOCK_SIZE_PIXELS + ChunksAsPixels(chunk_x),
                                                  y * BLOCK_SIZE_PIXELS + ChunksAsPixels(chunk_y),
                                                  width * BLOCK_SIZE_PIXELS, height * BLOCK_SIZE_PIXELS);
                }
            }
        }
    }
}
