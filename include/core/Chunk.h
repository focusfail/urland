#pragma once

#include "core/Block.h"
#include "core/Constants.h"

#include <raylib.h>
#include <array>

using BlockArray = std::array<Block, CHUNK_LENGTH_BLOCKS>;

class Chunk
{
public:
    Chunk() = default;
    void Init();
    void Render() const;
    void Update();
    void SetIndex(ChunkIndex index);

private:
    BlockArray _blocks;
    ChunkIndex _index = 0;
};