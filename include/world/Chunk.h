#ifndef URLAND_CHUNK_H
#define URLAND_CHUNK_H

#include "../core/Block.h"
#include "../core/BlockRegistry.h"
#include "../core/Constants.h"
#include "../core/Texture2DAtlas.h"

#include <raylib.h>

#include <array>
#include <memory>

using BlockArray = std::array<Block, CHUNK_LENGTH>;

class Chunk
{
public:
    Chunk();
    BlockArray& GetBlockArray();
    void Render(int chunk_index, const Texture2DAtlas& atlas, const BlockRegistry& br);
    void DrawBoundingBoxes();
    void Update();
    void GenerateBoundingBoxes();
    void PlaceBlock(float block_x, float block_y, Block block);
    const std::vector<Rectangle>& GetBoundingBoxes() const { return m_bbs; }

private:
    std::unique_ptr<BlockArray> m_blocks;
    std::vector<Rectangle> m_bbs;
    bool m_should_update_bb;
};

#endif // URLAND_CHUNK_H