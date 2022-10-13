/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** AssetManager
*/

#pragma once

#include <filesystem>

namespace ecs
{
    inline std::filesystem::path crossPlatformPath(std::filesystem::path path) { return path; }
    template <class... Args>
    std::filesystem::path crossPlatformPath(std::filesystem::path path, std::string_view next, Args... args)
    {
        return crossPlatformPath(path.append(next), args...);
    }
} // namespace ecs
