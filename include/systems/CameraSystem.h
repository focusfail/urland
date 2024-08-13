#ifndef URLAND_CAMERA_SYSTEM
#define URLAND_CAMERA_SYSTEM

#include <raylib.h>
#include <entt/entt.hpp>


struct CameraSystem {
    void Update(entt::registry& reg, Camera2D& camera);
};

#endif // URLAND_CAMERA_SYSTEM