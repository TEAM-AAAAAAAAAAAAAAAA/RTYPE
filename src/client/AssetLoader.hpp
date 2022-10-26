#pragma once

#include <string>
#include <map>
#include <memory>
#include <filesystem>
#include <SFML/Graphics.hpp>

/**
 * AssetLoader class which is used by the game to load assets
 */
namespace asset
{
    class AssetLoader {
      public:
        /**
         * Destroy the AssetLoader object
         */
        ~AssetLoader();

        /**
         * @brief load an SFML asset and add it to the map
         * @param path of the asset
         */
        static void LoadAsset(const std::filesystem::path &path);

        /**
         * @brief Get an Asset object from the map
         *
         * @param path of the asset to get
         * @return sf::Sprite& the asset
         */
        static sf::Texture &GetAsset(const std::filesystem::path &path);

        /**
         * the instance of the AssetLoader object
         */
        static AssetLoader _Instance;

      private:
        /**
         * Map of all the assets
         */
        std::map<std::string, sf::Texture> _assetsMap;


    };
} // namespace asset