#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <optional>
#include <string>

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
         * @brief end of smart path (you probably don't need to use this function)
         * @param key the key to load the asset
         * @param path of the asset
         */
        static inline void LoadTexture(const std::string &key, const std::filesystem::path &path);

        /**
         * @brief load an SFML asset and add it to the map
         * @param key the key to load the asset
         * @param path first segment of the path of the asset
         * @param next next segment of the path of the asset
         * @param args other segments of the path
         */
        template <class... Args>
        static void LoadTexture(
            const std::string &key, const std::filesystem::path &path, std::string_view next, Args... args)
        {
            sf::Texture texture;

            std::filesystem::path smart = smartPath(path, next, args...);

            if (!texture.loadFromFile(smart.generic_string()))
                return;
            _Instance._textureMap[key] = texture;
        }

        /**
         * @brief Get an Asset object from the map
         *
         * @param key of the asset to get
         * @return sf::Texture& the texture
         */
        static sf::Texture &GetTexture(const std::string &key);

        /**
         * the instance of the AssetLoader object
         */
        static AssetLoader _Instance;

        static inline std::filesystem::path smartPath(std::filesystem::path path) { return path; }

        template <class... Args>
        static std::filesystem::path smartPath(std::filesystem::path path, std::string_view next, Args... args)
        {
            return smartPath(path.append(next), args...);
        }

      private:
        /**
         * Map of all the assets
         */
        std::unordered_map<std::filesystem::path, sf::Texture> _textureMap;
    };
} // namespace asset