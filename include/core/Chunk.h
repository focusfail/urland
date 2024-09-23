#pragma once

#include "core/Block.h"
#include "core/Constants.h"

#include "components/RigidBody.h"
// #include "core/BlockArray.h"

#include <raylib.h>
#include <array>
#include <vector>

using BlockArray = std::array<Block, CHUNK_LENGTH_BLOCKS>;

class Chunk
{
public:
    Chunk() = default;
    ~Chunk();
    void Init();
    void Render(Texture2D* atlas) const;
    void Update();
    void SetIndex(ChunkIndex index);
    // Returns the blocks dynamic attributes (id, variation, light_level...)
    const Block& GetBlock(int block_index) const;

private:
    void m_GenerateBoundingBoxes();
    BlockArray m_blocks;
    ChunkIndex m_index = 0;
    std::vector<RigidBody> m_bounding_boxes = {};
    bool m_dirty = true;
};