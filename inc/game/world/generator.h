#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

#include "FastNoise/FastNoise.h"

#include "core/Constants.h"
#include "game/world/Chunk.h"

struct GenerationOptions
{
    //
    float surfaceLevel = 0.8f;
    float hillHeight = 36.0f;

    // Mountain noise settings
    int mountainOctaves = 2;
    float mountainGain = 0.3f;
    float mountainFrequency = 0.008f;
    int mountainSeed = 1234;

    // Biome/variation noise settings
    int biomeOctaves = 3;
    float biomeGain = 0.2f;
    float biomeFrequency = 0.005f;
    int biomeSeed = 5678;

    // Optional cave noise settings if you want to add those later
    bool generateCaves = false;
    float caveFrequency = 0.02f;
    float caveThreshold = 0.5f; // Values above this become caves

    static GenerationOptions Default()
    {
        GenerationOptions opts;
        opts.mountainOctaves = 2;
        opts.mountainGain = 0.3f;
        opts.mountainFrequency = 0.008f;
        opts.mountainSeed = 1234;
        opts.biomeOctaves = 3;
        opts.biomeGain = 0.2f;
        opts.biomeFrequency = 0.005f;
        opts.biomeSeed = 5678;
        return opts;
    }

    static GenerationOptions Mountainous()
    {
        GenerationOptions opts;
        opts.mountainOctaves = 4;
        opts.mountainGain = 0.5f;
        opts.mountainFrequency = 0.01f;
        opts.mountainSeed = 1234;
        opts.biomeOctaves = 3;
        opts.biomeGain = 0.3f;
        opts.biomeFrequency = 0.007f;
        opts.biomeSeed = 5678;
        return opts;
    }

    static GenerationOptions Plains()
    {
        GenerationOptions opts;
        opts.mountainOctaves = 2;
        opts.mountainGain = 0.2f;
        opts.mountainFrequency = 0.005f;
        opts.mountainSeed = 1234;
        opts.biomeOctaves = 2;
        opts.biomeGain = 0.15f;
        opts.biomeFrequency = 0.004f;
        opts.biomeSeed = 5678;
        return opts;
    }
};

class Generator
{
public:
    Generator();
    ~Generator() = default;

    void GenerateNoise(GenerationOptions opts = {});
    void ApplyNoise(Chunk& target);

private:
    std::vector<float> mMountainNoise = {};
    std::vector<float> mCaveNoise = {};
    std::vector<float> mBiomeNoise = {};
    GenerationOptions mOpts = {};
};

#endif // GENERATOR_H