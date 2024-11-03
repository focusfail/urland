#ifndef BLOCK_INFO_H
#define BLOCK_INFO_H

#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include "world/Block.h"

using nlohmann::json;
using BlockInfoArray = std::vector<BlockInfo>;

BlockInfoArray ParseBlocksJson(const char* filepath);
std::vector<std::string> ParseNames(const BlockInfoArray blockInfoArr);

extern const BlockInfoArray BLOCK_INFO;
// Map from block name to index into BLOCK_INFO or id;
extern const std::vector<std::string> BLOCK_NAME;

#endif // BLOCK_INFO_H
