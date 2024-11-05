#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "raylib.h"

/// @brief Rectangular body with collision, position and gravity
struct RigidBody
{
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    float velX = 0;
    float velY = 0;
    bool collides = true;
    bool hasGravity = true;

    RigidBody() = default;

    Vector2 GetCenter() const { return {x + width / 2.0f, y + height / 2.0f}; }

    RigidBody(float x, float y, float w, float h)
        : x(x)
        , y(y)
        , width(w)
        , height(h)
    {
    }

    RigidBody(const Rectangle& rect)
        : x(rect.x)
        , y(rect.y)
        , width(rect.width)
        , height(rect.height)
    {
    }
    operator Rectangle() const { return {x, y, width, height}; }
};

#endif // RIGID_BODY_H