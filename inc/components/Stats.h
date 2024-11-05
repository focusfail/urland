#ifndef STATS_H
#define STATS_H

struct Stats
{
    float health = 100.0f;
    float reach = 4.0f;      // Interaction-reach in blocks
    float speed = 500.0f;    // Base speed
    float sprintMul = 1.75f; // Sprint speed multiplier
};

#endif // STATS_H