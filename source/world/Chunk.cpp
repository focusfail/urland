#include "world/Chunk.h"

#include <rlgl.h>

Chunk::Chunk()
    : m_blocks(std::make_unique<BlockArray>())
{
    // Fill the chunk with air
    std::fill(m_blocks->begin(), m_blocks->end(), Block {0, 1, 15});
    GenerateBoundingBoxes();
}

BlockArray& Chunk::GetBlockArray() { return *m_blocks; }

void Chunk::Render(int chunk_index, const Texture2DAtlas& atlas, const BlockRegistry& br)
{
    float chunk_x = chunk_index % WORLD_WIDTH;
    float chunk_y = chunk_index / WORLD_WIDTH;

    for (size_t i = 0; i < CHUNK_LENGTH; i++) {
        Block& block = m_blocks->at(i);
        int tex_id = br.GetTextureID(block);

        float local_x = i % CHUNK_SIZE;
        float local_y = i / CHUNK_SIZE;

        float global_x = local_x * BLOCK_SIZE + (chunk_x * CHUNK_PIXEL_SIZE);
        float global_y = local_y * BLOCK_SIZE + (chunk_y * CHUNK_PIXEL_SIZE);

        Color tint = {255, 255, 255, 255};
        if (block.light_level == 0) { tint = {0, 0, 0, 255}; }

        atlas.DrawSprite(tex_id, global_x, global_y, tint);
    }
}

void Chunk::Update()
{
    if (m_should_update_bb) { GenerateBoundingBoxes(); }
}

void Chunk::PlaceBlock(float block_x, float block_y, Block block)
{
    int local_x = static_cast<int>(block_x / BLOCK_SIZE) % CHUNK_SIZE;
    int local_y = static_cast<int>(block_y / BLOCK_SIZE) % CHUNK_SIZE;
    int block_index = local_y * CHUNK_SIZE + local_x;

    m_blocks->at(block_index) = block;

    const BlockRegistry& br = BlockRegistry::GetInstance();
    if (br.IsSolid(block.id)) m_should_update_bb = true;
}

void Chunk::GenerateBoundingBoxes()
{
    m_bbs.clear();
    const BlockRegistry& br = BlockRegistry::GetInstance();

    bool visited[CHUNK_SIZE][CHUNK_SIZE] = {false};

    for (int y = 0; y < CHUNK_SIZE; ++y) {
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            if (!visited[y][x]) {
                int block_index = y * CHUNK_SIZE + x;
                Block& block = m_blocks->at(block_index);

                if (br.IsSolid(block.id)) {
                    int width = 1;
                    int height = 1;

                    // Expand horizontally
                    while (x + width < CHUNK_SIZE && !visited[y][x + width] &&
                           br.IsSolid(m_blocks->at(y * CHUNK_SIZE + (x + width)).id)) {
                        ++width;
                    }

                    // Expand vertically
                    bool can_expand_vertically = true;
                    while (can_expand_vertically && y + height < CHUNK_SIZE) {
                        for (int i = 0; i < width; ++i) {
                            if (visited[y + height][x + i] ||
                                !br.IsSolid(m_blocks->at((y + height) * CHUNK_SIZE + (x + i)).id)) {
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
                    m_bbs.emplace_back(x * BLOCK_SIZE, y * BLOCK_SIZE, width * BLOCK_SIZE, height * BLOCK_SIZE);
                }
            }
        }
    }
}

void Chunk::DrawBoundingBoxes()
{
    for (auto bb : m_bbs) {
        // adjust for bb outline
        bb.x += 2.0f;
        bb.y += 2.0f;
        bb.width -= 2.0f;
        bb.height -= 2.0f;
        DrawRectangleRoundedLinesEx(bb, 0.0f, 1, 2.0f, Color {0, 255, 255, 255});
    }
}