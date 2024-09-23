#include "core/Block.h"

static std::ifstream f("C:\\code\\urland\\assets\\blocks.jsonc");
json g_block_data = json::parse(f, nullptr, true, true)["blocks"];

inline std::unordered_map<std::string, uint8_t> ParseBlockIds()
{
    std::unordered_map<std::string, uint8_t> names;
    int i = 0;
    for (auto block : g_block_data) { names[block["name"]] = ++i; }

    return names;
}

std::unordered_map<std::string, uint8_t> g_block_name_to_id = ParseBlockIds();

Block CreateBlock(std::string name, uint8_t var)
{
    uint8_t id = g_block_name_to_id[name];
    uint8_t texture_id = (uint8_t)g_block_data[id]["texture_id"] + var;
    bool is_solid = g_block_data[id]["is_solid"];

    return Block {id, 15, var, texture_id, is_solid};
}