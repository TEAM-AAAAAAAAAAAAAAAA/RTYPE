/*
** EPITECH PROJECT, 2022
** R-TYPEMIRROR
** File description:
** AssetLoader
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <unordered_map>

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
        ~AssetLoader() = default;

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

        static void LoadTexture(const std::string &key, std::vector<std::string> paths)
        {
            sf::Texture texture;

            std::filesystem::path smart = smartPath(paths);

            if (!texture.loadFromFile(smart.generic_string()))
                return;
            _Instance._textureMap[key] = texture;
        }

        /**
         * @brief create a smartpath from a vector of string
         *
         */
        static std::filesystem::path smartPath(std::vector<std::string> paths)
        {
            std::filesystem::path smart = paths[0];

            for (int i = 1; i < paths.size(); i++) {
                smart.append(paths[i]);
            }
            return smart;
        }

        /**
         * @brief Get an Asset object from the map
         *
         * @param key of the asset to get
         * @return sf::Texture& the texture
         */
        static sf::Texture &GetTexture(const std::string &key) { return _Instance._textureMap[key]; }

        /**
         * @brief Load a .ini file with boost loading assets into the map
         *
         */
        static void LoadIniFile(const std::filesystem::path &path)
        {
            boost::property_tree::ptree pt;
            try {
                boost::property_tree::ini_parser::read_ini(path.generic_string(), pt);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }

            // loop through the sections
            for (auto &section : pt) {
                for (auto &value : section.second) {
                    std::vector<std::string> paths;
                    // parse the section.second with slash and put it in the vector
                    while (value.second.data().find("/") != std::string::npos) {
                        paths.push_back(value.second.data().substr(0, value.second.data().find("/")));
                        value.second.data().erase(0, value.second.data().find("/") + 1);
                    }
                    paths.push_back(value.second.data());
                    LoadTexture(value.first.data(), paths);
                }
            }
        }

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

        static void display_key_from_map()
        {
            std::cout << "len of map: " << _Instance._textureMap.size() << std::endl;
            for (auto &key : _Instance._textureMap) {
                std::cout << key.first << std::endl;
            }
        }

      private:
        /**
         * Map of all the assets
         */
        std::unordered_map<std::string, sf::Texture> _textureMap;
    };
} // namespace asset