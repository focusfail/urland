#include "game/BlockInfo.h"

#include <fstream>
#include <iostream>

BlockInfoArray ParseBlocksJson(const char* filepath)
{
    BlockInfoArray blocksInfo;
    std::fstream f(filepath);
    json blocksInfoJson = json::parse(f, nullptr, true, true);

    int id = 0;
    for (const auto& blockInfo : blocksInfoJson["blocks"]) {
        bool isSolid = blockInfo["is_solid"];
        std::cout << id << blockInfo["name"] << ": " << isSolid << "\n";
        blocksInfo.emplace_back(isSolid);
        id++;
    }

    return blocksInfo;
}

// Define and initialize BLOCK_INFO
const BlockInfoArray BLOCK_INFO = ParseBlocksJson("c:/code/urland/assets/blocks.jsonc");
