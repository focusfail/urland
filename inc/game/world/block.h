#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>

struct BlockInfo
{
    bool isSolid;
};

struct Block
{
    unsigned int id = 1;
};

#endif // BLOCK_H