#pragma once

#include "core/Constants.h"
#include <raylib.h>

struct RigidBody
{
    WorldCoordinate x, y;
    float width, height;
    float velocity_x = 0.0f, velocity_y = .0f;
    float friction = 0.0f;
    bool collides = true;

    void ApplyForce(float vel_x, float vel_y)
    {
        this->velocity_x += vel_x;
        this->velocity_y += vel_y;
    }

    Vector2 TopLeft() const { return Vector2(x, y); }
    Vector2 Center() const { return Vector2(x + width / 2.0f, y + height / 2.0f); };

    operator Rectangle() const { return Rectangle(x, y, width, height); }
};