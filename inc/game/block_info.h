#ifndef BLOCK_INFO_H
#define BLOCK_INFO_H

#include <vector>
#include "nlohmann/json.hpp"
#include "world/block.h"

using nlohmann::json;
using BlockInfoArray = std::vector<BlockInfo>;

BlockInfoArray ParseBlocksJson(const char* filepath);

extern const BlockInfoArray BLOCK_INFO;

#endif // BLOCK_INFO_H
