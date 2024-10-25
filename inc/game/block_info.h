#ifndef BLOCK_INFO_H
#define BLOCK_INFO_H

#include <fstream>
#include <iostream>
#include <vector>
#include "nlohmann/json.hpp"
#include "world/block.h"

using nlohmann::json;
using BlockInfoArray = std::vector<BlockInfo>;

inline BlockInfoArray ParseBlocksJson(const char* filepath)
{
    BlockInfoArray blocksInfo(32);
    std::fstream f(filepath);
    json blocksInfoJson = json::parse(f, NULL, true, true);

    for (const auto& blockInfo : blocksInfoJson["blocks"]) {
        bool isSolid = blockInfo["is_solid"];
        blocksInfo.emplace_back(isSolid);
    }

    return blocksInfo;
}

inline static const BlockInfoArray BLOCK_INFO = ParseBlocksJson("c:/code/urland/assets/blocks.jsonc");

#endif // BLOCK_INFO_H