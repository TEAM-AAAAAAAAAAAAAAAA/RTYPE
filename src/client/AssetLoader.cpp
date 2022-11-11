/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Server
*/

#include "AssetLoader.hpp"

namespace asset
{
    AssetLoader &AssetLoader::getInstance()
    {
        static AssetLoader _Instance;
        return _Instance;
    }
} // namespace asset