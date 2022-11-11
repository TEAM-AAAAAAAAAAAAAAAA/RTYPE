/*
** EPITECH PROJECT, 2022
** R-TYPEMIRROR
** File description:
** AssetLoader
*/

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <unordered_map>
#include <utility>

namespace asset
{
    /**
     * This class loads all the assets neened by the game and stores them in a map
     * Basic operatations on assets are supported
     * An asset is either a texture, a sound or a font
     */
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
            getInstance()._textureMap[key] = texture;
        }

        static void LoadTexture(const std::string &key, std::vector<std::string> paths)
        {
            sf::Texture texture;

            std::filesystem::path smart = smartPath(std::move(paths));

            if (!texture.loadFromFile(smart.generic_string()))
                return;
            getInstance()._textureMap[key] = texture;
        }

        /**
         * @brief Load a background music and add it to the map
         * @tparam Args Path segments
         * @param key the key to load the asset
         * @param path first segment of the path of the asset
         * @param next next segment of the path of the asset
         * @param args other segments of the path
         */
        template <class... Args>
        static void LoadBGM(
            const std::string &key, const std::filesystem::path &path, std::string_view next, Args... args)
        {
            std::filesystem::path smart = smartPath(path, next, args...);

            if (!getInstance()._bgmMap[key].openFromFile(smart.generic_string()))
                return;
        }

        static void LoadBGM(const std::string &key, std::vector<std::string> paths)
        {
            std::filesystem::path smart = smartPath(std::move(paths));

            if (!getInstance()._bgmMap[key].openFromFile(smart.generic_string()))
                return;
        }

        /**
         * @brief Load a sound effect and add it to the map
         * @tparam Args Path segments
         * @param key the key to load the asset
         * @param path first segment of the path of the asset
         * @param next next segment of the path of the asset
         * @param args other segments of the path
         */
        template <class... Args>
        static void LoadSFX(
            const std::string &key, const std::filesystem::path &path, std::string_view next, Args... args)
        {
            std::filesystem::path smart = smartPath(path, next, args...);

            if (!getInstance()._sfxBufferMap[key].loadFromFile(smart.generic_string()))
                return;
            getInstance()._sfxMap[key].setBuffer(getInstance()._sfxBufferMap[key]);
        }

        static void LoadSFX(const std::string &key, std::vector<std::string> paths)
        {
            std::filesystem::path smart = smartPath(std::move(paths));

            if (!getInstance()._sfxBufferMap[key].loadFromFile(smart.generic_string()))
                return;
            getInstance()._sfxMap[key].setBuffer(getInstance()._sfxBufferMap[key]);
        }

        /**
         * @brief load a font and add it to the map
         * @param key the key to load the font
         * @param path first segment of the path of the font
         * @param next next segment of the path of the font
         * @param args other segments of the path
         */
        template <class... Args>
        static void LoadFont(
            const std::string &key, const std::filesystem::path &path, std::string_view next, Args... args)
        {
            sf::Font font;

            std::filesystem::path smart = smartPath(path, next, args...);

            if (!font.loadFromFile(smart.generic_string()))
                return;
            getInstance()._fontMap[key] = font;
        }

        static void LoadFont(const std::string &key, std::vector<std::string> paths)
        {
            sf::Font font;

            std::filesystem::path smart = smartPath(std::move(paths));

            if (!font.loadFromFile(smart.generic_string()))
                return;
            getInstance()._fontMap[key] = font;
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
         * @param key of the asset to get
         * @return sf::Texture& the texture
         */
        static sf::Texture &GetTexture(const std::string &key) { return getInstance()._textureMap[key]; }

        /**
         * @brief Get a background music object from the map
         * @param key of the asset to get
         * @return sf::Music& the music
         */
        static sf::Music &GetBGM(const std::string &key) { return getInstance()._bgmMap[key]; }

        /**
         * @brief Get a sound effect object from the map
         * @param key of the asset to get
         * @return sf::Sound& the sound effect
         */
        static sf::Sound &GetSFX(const std::string &key) { return getInstance()._sfxMap[key]; }

        /**
         * @brief Get a font object from the mapb
         * @param key of the asset to get
         * @return sf::Font& the font
         */
        static sf::Font &GetFont(const std::string &key) { return getInstance()._fontMap[key]; }

        /**
         * @brief Load a .ini file with boost loading assets into the map
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
                    while (value.second.data().find('/') != std::string::npos) {
                        paths.push_back(value.second.data().substr(0, value.second.data().find('/')));
                        value.second.data().erase(0, value.second.data().find('/') + 1);
                    }
                    paths.push_back(value.second.data());

                    if (section.first == "texture")
                        LoadTexture(value.first, paths);
                    if (section.first == "bgm")
                        LoadBGM(value.first, paths);
                    if (section.first == "sfx")
                        LoadSFX(value.first, paths);
                    if (section.first == "font")
                        LoadFont(value.first, paths);
                }
            }
        }

        /**
         * the instance of the AssetLoader object
         */
        static AssetLoader &getInstance();

            static inline std::filesystem::path smartPath(std::filesystem::path path) { return path; }

        template <class... Args>
        static std::filesystem::path smartPath(std::filesystem::path path, std::string_view next, Args... args)
        {
            return smartPath(path.append(next), args...);
        }

        static void display_key_from_map()
        {
            std::cout << "len of map: " << getInstance()._textureMap.size() << std::endl;
            for (auto &key : getInstance()._textureMap) {
                std::cout << key.first << std::endl;
            }
        }

      private:
        /**
         * Map of all the assets
         */
        std::unordered_map<std::string, sf::Texture> _textureMap;

        /**
         * Map of all the background music
         */
        std::unordered_map<std::string, sf::Music> _bgmMap;

        /**
         * Map of all the sound buffer used by the `sf::Sounds` inside
         */
        std::unordered_map<std::string, sf::SoundBuffer> _sfxBufferMap;

        /**
         * Map of all the sound effects
         */
        std::unordered_map<std::string, sf::Sound> _sfxMap;

        /**
         * Map of all the fonts
         */
        std::unordered_map<std::string, sf::Font> _fontMap;
    };
} // namespace asset