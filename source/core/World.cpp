#include "core/World.h"
#include "core/Convertions.h"

#include <raylib.h>
#include <iostream>
#include <chrono>

World::World()
    : m_chunks(std::make_unique<ChunkArray>())
{
    // Reserve max amount of active chunks
    m_active_chunks.reserve((CHUNKS_AROUND_PLAYER + 1) * (CHUNKS_AROUND_PLAYER + 1));
}

void World::Init(Texture2D* block_atlas)
{
    m_block_atlas = block_atlas;

    for (size_t chunk_i = 0; chunk_i < m_chunks->size(); chunk_i++) {
        Chunk& chunk = m_chunks->at(chunk_i);
        chunk.SetIndex(chunk_i);
        chunk.Init();
    }

    TraceLog(LOG_INFO, "World: Initialized chunks.");
}

void World::Render() const
{
    using namespace std::chrono;

    long long total_duration = 0; // Accumulate total duration
    int chunk_count = 0;          // Count the number of chunks rendered

    for (int index : m_active_chunks) {
        auto start = high_resolution_clock::now(); // Start timing

        m_chunks->at(index).Render(m_block_atlas);

        auto end = high_resolution_clock::now();                          // End timing
        auto duration = duration_cast<microseconds>(end - start).count(); // Calculate duration in microseconds

        total_duration += duration; // Accumulate duration
        chunk_count++;              // Increment chunk count
    }

    if (chunk_count > 0) {
        auto average_duration = total_duration / chunk_count; // Calculate average duration
        std::cout << "Average chunk render time: " << average_duration << " microseconds. \n"; // Print average duration
    }
}

void World::Update(entt::registry& registry, Camera2D& camera)
{
    auto [chunk_x, chunk_y] = WorldToChunkPosition(camera.target.x, camera.target.y);

    m_active_chunks.clear();

    for (int y = chunk_y - CHUNKS_AROUND_PLAYER; y <= chunk_y + CHUNKS_AROUND_PLAYER; y++) {
        if (y < 0 || y >= WORLD_HEIGHT_CHUNKS) continue;
        for (int x = chunk_x - CHUNKS_AROUND_PLAYER; x <= chunk_x + CHUNKS_AROUND_PLAYER; x++) {
            if (x < 0 || x >= WORLD_WIDTH_CHUNKS) continue;

            int chunk_index = ChunkPositionToIndex(x, y);
            m_chunks->at(chunk_index).Update();
            m_active_chunks.push_back(chunk_index);
        }
    }
}