cmake_minimum_required(VERSION 3.10)
project(urland VERSION 0.2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

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
    noise
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

FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(entt)
FetchContent_MakeAvailable(noise)
FetchContent_MakeAvailable(json)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    # ${CMAKE_SOURCE_DIR}/inc/core
    # ${CMAKE_SOURCE_DIR}/inc/game
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib EnTT::EnTT FastNoise nlohmann_json)