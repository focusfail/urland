#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <stdint.h>
#include <nlohmann/json.hpp>

using nlohmann::json;

extern json g_block_data;
extern std::unordered_map<std::string, uint8_t> g_block_name_to_id;

struct Block
{
    uint8_t id = 0;
    uint8_t light_level = 1;
    uint8_t specific_variation = 0;
    uint8_t texture_id = 0;
    bool is_solid = false;
};

extern Block CreateBlock(std::string name, uint8_t var);