#include "core/BlockRegistry.h"

#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

BlockRegistry::BlockRegistry() { }

BlockRegistry& BlockRegistry::GetInstance()
{
    static BlockRegistry instance;
    return instance;
}

void BlockRegistry::LoadFromJson(const char* path)
{
    std::ifstream file(path);
    json data = json::parse(file, nullptr, true, true);

    m_blocks.clear();
    m_breakable_blocks.clear();
    m_solid_blocks.clear();
    m_id_to_tool.clear();
    m_name_to_id.clear();

    int id = 0;
    for (const auto& block : data["blocks"]) {
        StaticBlockData block_data;
        block_data.name = block["name"];
        block_data.texture_id = block["texture_id"];
        block_data.variations = block["variations"];
        block_data.is_solid = block["is_solid"];
        block_data.is_transparent = block["is_transparent"];
        block_data.mining_level = block["mining_level"];
        block_data.tool = block["tool"];

        for (auto& loot : block["loot_pool"]) { block_data.loot_pool.push_back(static_cast<string>(loot)); }

        m_blocks.push_back(block_data);
        m_id_to_tool.push_back(block_data.tool);
        m_name_to_id[block_data.name] = id;

        if (block_data.is_solid) { m_solid_blocks.insert(id); }

        if (block_data.tool != "none") { m_breakable_blocks.insert(id); }

        id++;
    }
}

const BlockRegistry::StaticBlockData& BlockRegistry::DataByID(unsigned int id) const { return m_blocks.at(id); }
const BlockRegistry::StaticBlockData& BlockRegistry::DataByName(string name) const
{
    return m_blocks.at(m_name_to_id.at(name));
}
bool BlockRegistry::IsSolid(unsigned int id) const { return m_solid_blocks.contains(id); }
bool BlockRegistry::IsBreakable(unsigned int id) const { return m_breakable_blocks.contains(id); }
bool BlockRegistry::CanMine(unsigned int id, string tool) const { return m_id_to_tool.at(id) == tool; }

unsigned int BlockRegistry::GetTextureID(const Block& block) const
{
    const StaticBlockData& block_data = m_blocks.at(block.id);
    return block_data.texture_id + block.variation - 1;
}

int BlockRegistry::GetNumBlocks() const { return m_blocks.size(); }