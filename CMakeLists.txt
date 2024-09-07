cmake_minimum_required(VERSION 3.20)
project(urland VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_COMPILER "C:/.msys64/mingw64/bin/clang++.exe")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Adding Raylib
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
    raygui
    GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
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
FetchContent_MakeAvailable(raygui)
FetchContent_MakeAvailable(entt)
FetchContent_MakeAvailable(noise)
FetchContent_MakeAvailable(json)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
include_directories(
    ${raygui_SOURCE_DIR}/src 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/components
    ${CMAKE_SOURCE_DIR}/include/systems
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/scenes
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib EnTT::EnTT FastNoise nlohmann_json)
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets" GAME_VERSION="${PROJECT_VERSION}") 
