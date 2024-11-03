#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <string>
#include <filesystem>
#include <format>
#include <iostream>

#include "raylib.h"

inline std::string GetPath(std::filesystem::path targetPath)
{
    // Print current working directory for debugging
    std::cout << "INFO: [FILESYS] Current working directory: " << std::filesystem::current_path() << std::endl;

    auto devPath = std::filesystem::absolute(".." / targetPath);
    auto distPath = std::filesystem::absolute("." / targetPath);

    // Print both paths we're checking
    std::cout << "INFO: [FILESYS] Checking dev path: " << std::filesystem::absolute(devPath) << std::endl;
    std::cout << "INFO: [FILESYS] Checking dist path: " << std::filesystem::absolute(distPath) << std::endl;

    if (std::filesystem::exists(devPath)) {
        std::cout << "INFO: [FILESYS] Using dev path: " << devPath << std::endl;
        return devPath.string();
    }
    else if (std::filesystem::exists(distPath)) {
        std::cout << "INFO: [FILESYS] Using dist path: " << distPath << std::endl;
        return distPath.string();
    }
    else {
        std::cout << "INFO: [FILESYS] Neither path exists!" << std::endl;
        // Maybe throw an exception or handle the error case
        return distPath.string();
    }
}

#endif // PATH_MANAGER_H