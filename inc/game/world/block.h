#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <string>

struct BlockInfo
{
    bool isSolid = true;
    int numVariants = 1;
    int textureID = 0;
    std::string name;
};

struct Block
{
    unsigned int id = 0;
    unsigned int variant = 1;
    float health = 1.0f;
};

#endif // BLOCK_H