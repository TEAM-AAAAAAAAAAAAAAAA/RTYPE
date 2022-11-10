/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AudioManager
*/

#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <vector>

namespace audio
{

    /**
     * This class manages all the sounds and musics of the game
     * Basic operations on background musics and sound effects are supported
     */
    class AudioManager {
      public:
        ~AudioManager() = default;

        /**
         * @brief load a background music to be played
         * @param key the key relative to the AssetLoader
         * @return true if the music was loaded
         */
        static bool loadBGM(const std::string &key);

        /**
         * play the current background music
         * @param loop if the music should loop, defaulted to true
         * @param volume the volume of the music, defaulted to 100
         * @return true if the music is playing, false otherwise
         */
        static bool playBGM(bool loop = true);

        /**
         * stop the current background music
         * @return true if the music is stopped, false otherwise
         */
        static bool stopBGM();

        /**
         * Set the background music volume
         * @param volume, 0 = min, 100 = max
         * @return true if the volume is set, false otherwise
         */
        static bool setBGMVolume(float volume);

        [[nodiscard]] static float getBGMVolume();

        [[nodiscard]] static sf::SoundSource::Status getBGMStatus();

        /**
         * Set whether or not the stream should loop after reaching the end.
         * @param loop true to play in loop, false to play once
         */
        static void loopBGM(bool loop);

        /**
         * @brief load a sound effect to be played
         * @param key the key relative to the AssetLoader
         * @deprecated
         * @warning Do not use, this is for development only
         */
        static void loadSFX(const std::string &key);

        static void playSFX(const std::string &key);

        /**
         *  Set the sound effects volume
         * @param volume, 0 = min, 100 = max
         * @return true if the volume is set, false otherwise
         */
        static void setSFXVolume(float volume);

        [[nodiscard]] static float getSFXVolume();

      private:
        AudioManager() = default;

        /**
         * Current BGM music key
         */
        std::string _currentBGMKey;

        /**
         * Queue of sound effects to play
         */
        std::string _currentSFXKey;

        /**
         * The volume of the background music
         */
        float _BGMVolume = 50.0f;

        /**
         * The volume of the sound effects
         */
        float _SFXVolume = 50.0f;

        /**
         * Instance of the AudioManager, lazy loaded
         */
        static AudioManager &getInstance();
    };
} // namespace audio
