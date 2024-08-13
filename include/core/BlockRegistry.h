/*
A singleton register that contains static information per block type.
*/

#ifndef URLAND_BLOCK_REGISTRY_H
#define URLAND_BLOCK_REGISTRY_H

#include "core/Block.h"

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using std::string, std::vector, std::unordered_map, std::set;

class BlockRegistry
{
public:
    struct StaticBlockData {
        string name;
        string tool;
        bool is_solid;
        bool is_transparent;
        unsigned int texture_id;
        unsigned int variations;
        unsigned int mining_level;
        vector<string> loot_pool;
    };

public:
    int GetNumBlocks() const;
    /// @brief returns static block data about a block type by block id
    const StaticBlockData& DataByID(unsigned int id) const;
    /// @brief returns static block data about a block type by block name
    const StaticBlockData& DataByName(string name) const;
    /// @brief validate whether a block is solid or not
    bool IsSolid(unsigned int id) const;
    /// @brief validate whether a block is breakable or not
    bool IsBreakable(unsigned int id) const;
    /// @brief validate whether a block is mineable or not
    bool CanMine(unsigned int id, string tool) const;
    /// @brief returns the texture id of a block and its variation
    unsigned int GetTextureID(const Block& block) const;

    static BlockRegistry& GetInstance();

    void LoadFromJson(const char* path);

private:
    BlockRegistry();
    BlockRegistry(const BlockRegistry&) = delete;
    BlockRegistry& operator=(const BlockRegistry&) = delete;
    set<unsigned int> m_solid_blocks;
    set<unsigned int> m_breakable_blocks;
    unordered_map<string, int> m_name_to_id;
    vector<string> m_id_to_tool;
    vector<StaticBlockData> m_blocks;
};

#endif // URLAND_BLOCK_REGISTRY_H