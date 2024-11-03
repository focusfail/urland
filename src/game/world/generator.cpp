#include "game/world/Generator.h"

#include <chrono>
#include <format>
#include <iostream>
#include "raylib.h"

#include "game/BlockInfo.h"
#include "util/RandomUtil.h"

Generator::Generator()
    : mMountainNoise(TERRAIN_WIDTH_BLOCKS)
    , mBiomeNoise(TERRAIN_WIDTH_BLOCKS)
    , mCaveNoise(TERRAIN_WIDTH_BLOCKS * TERRAIN_HEIGHT_BLOCKS)
{
}

void Generator::GenerateNoise(GenerationOptions opts)
{
    mOpts = opts;
    auto timeA = std::chrono::high_resolution_clock::now();

    // Mountain noise generation
    auto fractalFbm = FastNoise::New<FastNoise::FractalFBm>();
    auto simplex = FastNoise::New<FastNoise::Simplex>();
    fractalFbm->SetSource(simplex);
    fractalFbm->SetOctaveCount(opts.mountainOctaves);
    fractalFbm->SetGain(opts.mountainGain);

    fractalFbm->GenUniformGrid2D(mMountainNoise.data(), 0, 0, TERRAIN_WIDTH_BLOCKS, 1, opts.mountainFrequency,
                                 opts.mountainSeed);

    // Biome/variation noise generation
    auto variationNoise = FastNoise::New<FastNoise::FractalFBm>();
    auto variationSimplex = FastNoise::New<FastNoise::Simplex>();
    variationNoise->SetSource(variationSimplex);
    variationNoise->SetOctaveCount(opts.biomeOctaves);
    variationNoise->SetGain(opts.biomeGain);

    variationNoise->GenUniformGrid2D(mBiomeNoise.data(), 0, 0, TERRAIN_WIDTH_BLOCKS, 1, opts.biomeFrequency,
                                     opts.biomeSeed);

    auto timeB = std::chrono::high_resolution_clock::now();
    auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA);
    TraceLog(LOG_INFO, std::format("WORLDGEN: Generated world noise in: {} ms", timeTaken.count()).c_str());
}
void Generator::ApplyNoise(Chunk& target)
{
    Block air = Block();
    air.id = 0;
    Block dirt = Block();
    dirt.id = 1;
    Block grass = Block();
    grass.id = 2;
    Block stone = Block();
    stone.id = 3;

    auto& targetBlocks = target.GetBlocks();
    targetBlocks.fill(air);
    Rectangle area = target.GetAreaBlocks();

    // Adjust ground level and variation
    const int groundLevel = static_cast<int>(TERRAIN_HEIGHT_BLOCKS * (1.0f - mOpts.surfaceLevel));

    for (int x = area.x; x < CHUNK_SIZE_BLOCKS + area.x; x++) {
        // Combine noises with reduced intensity and smoothing
        float mainNoise = mMountainNoise[x];
        float variationNoise = mBiomeNoise[x];

        // Calculate height offset from ground level
        float heightOffset = (mainNoise * 0.7f + variationNoise * 0.3f) * mOpts.hillHeight;

        // Calculate final surface height
        int surfaceHeight = groundLevel + static_cast<int>(heightOffset);

        for (int y = area.y; y < CHUNK_SIZE_BLOCKS + area.y; y++) {
            int blockIndex = (y - area.y) * CHUNK_SIZE_BLOCKS + (x - area.x);

            // Determine block type based on depth from surface
            if (y < surfaceHeight) { targetBlocks[blockIndex] = air; }
            else if (y == surfaceHeight) {
                targetBlocks[blockIndex] = grass;
                targetBlocks[blockIndex].variant = GetRandomNumber(1, BLOCK_INFO[grass.id].numVariants);
            }
            else if (y <= surfaceHeight + 3) {
                targetBlocks[blockIndex] = dirt;
                targetBlocks[blockIndex].variant = GetRandomNumber(1, BLOCK_INFO[dirt.id].numVariants);
            }
            else {
                targetBlocks[blockIndex] = stone;
                targetBlocks[blockIndex].variant = GetRandomNumber(1, BLOCK_INFO[stone.id].numVariants);
            }
        }
    }
}