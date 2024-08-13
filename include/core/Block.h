#ifndef URLAND_BLOCK_H
#define URLAND_BLOCK_H

#include <cstdint>

struct Block {
    uint8_t id = 0;
    uint8_t variation = 1;
    uint8_t light_level = 0;
};

static const Block BLOCK_AIR = Block {0, 1, 0};

#endif // URLAND_BLOCK_H