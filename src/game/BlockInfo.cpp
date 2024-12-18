#include "game/BlockInfo.h"

#include <fstream>
#include <iostream>

#include "util/PathManager.h"

BlockInfoArray ParseBlocksJson(const char* filepath)
{
    BlockInfoArray blocksInfo;
    std::cout << "INFO: [FILESYS] Parsing json: " << filepath << "\n";
    std::fstream f(filepath);
    json blocksInfoJson = json::parse(f, nullptr, true, true);

    int id = 0;
    for (const auto& blockInfo : blocksInfoJson["blocks"]) {
        bool isSolid = blockInfo["is_solid"];
        int textureID = blockInfo["texture_id"];
        int numVariants = blockInfo["variations"];
        std::string name = blockInfo["name"];
        blocksInfo.emplace_back(isSolid, numVariants, textureID, name);
        id++;
    }

    return blocksInfo;
}

std::vector<std::string> ParseNames(const BlockInfoArray blockInfoArr)
{
    std::vector<std::string> names;
    names.reserve((blockInfoArr.size()));

    for (const BlockInfo& info : blockInfoArr) { names.emplace_back(info.name); }

    return names;
}

// Define and initialize BLOCK_INFO
const BlockInfoArray BLOCK_INFO = ParseBlocksJson(GetPath("assets/blocks.jsonc").c_str());
const std::vector<std::string> BLOCK_NAME = ParseNames(BLOCK_INFO);
