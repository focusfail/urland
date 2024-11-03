# urland

## Overview

A terraria-like game written in C++. The game is not meant to become a complete game as of now. Instead it's just a passion project of mine.

## Features

- Simple entity viewer allows editing entities' components
- Debug window with many functions
- Chunked rendering & update
- Json format for block description

## Building for Windows

### Requirements

- CMake
- Clang++

### Steps

1. Clone the repository

    ```bash
    git clone https://github.com/focusfail/urland.git
    cd urland
    ```

2. Building

    ```bash
    cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER:FILEPATH="/path/to/clang.exe" -DCMAKE_CXX_COMPILER:FILEPATH="/path/to/clang++.exe" -S . -B ./build
    ```
3. Compile
    ```bash
    cmake --build .\build\ --config Release
    ```
4. Run
    ```bash
    ./build/urland.exe
    ```

## Controls

| **Action**       | **Key/Button** |
|------------------|-----------------|
| Move Up          | `W`            |
| Move Down        | `S`            |
| Move Left        | `A`            |
| Move Right       | `D`            |
| Debug Window     | `F7`           |

## Demo

![Demo Image - urland 0.2.0](https://github.com/focusfail/urland/blob/master/demo/DemoImg.png)
