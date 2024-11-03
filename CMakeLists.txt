cmake_minimum_required(VERSION 3.10)
project(urland VERSION 0.2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(IMGUI_BUILD_EXAMPLES OFF)

set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")
set(FETCHCONTENT_SOURCE_DIR "${FETCHCONTENT_BASE_DIR}")

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    entt
    GIT_REPOSITORY "https://github.com/skypjack/entt.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    fastnoise2
    GIT_REPOSITORY "https://github.com/Auburn/FastNoise2.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    json
    GIT_REPOSITORY "https://github.com/nlohmann/json.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    rl_imgui
    GIT_REPOSITORY "https://github.com/raylib-extras/rlImGui.git"
    GIT_TAG "main"
    GIT_PROGRESS TRUE
)    


FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(entt)
FetchContent_MakeAvailable(fastnoise2)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(rl_imgui)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(RL_IMGUI_SOURCES ${rl_imgui_SOURCE_DIR}/rlImGui.cpp)
set(IMGUI_SOURCES  
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
)


include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${rl_imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${RL_IMGUI_SOURCES} ${IMGUI_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib EnTT::EnTT FastNoise nlohmann_json )