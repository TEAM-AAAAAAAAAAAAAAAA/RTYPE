/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AudioManager
*/

#pragma once

#include <string>
#include <vector>

namespace audio {

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
			bool loadBGM(const std::string &key);

			/**
			 * play the current background music
			 * @param loop if the music should loop, defaulted to true
			 * @param volume the volume of the music, defaulted to 100
			 * @return true if the music is playing, false otherwise
			 */
			bool playBGM(bool loop = true);

			/**
			 * stop the current background music
			 * @return true if the music is stopped, false otherwise
			 */
			bool stopBGM();

			/**
			 * Set the background music volume
			 * @param volume, 0 = min, 100 = max
			 * @return true if the volume is set, false otherwise
			 */
			bool setBGMVolume(float volume);

			/**
			 * Set whether or not the stream should loop after reaching the end.
			 * @param loop true to play in loop, false to play once
			 */
			void loopBGM(bool loop);

			/**
			 * @brief load a sound effect to be played
			 * @param key the key relative to the AssetLoader
			 */
			void loadSFX(const std::string &key);

			/**
			 *  Set the sound effects volume
			 * @param volume, 0 = min, 100 = max
			 * @return true if the volume is set, false otherwise
			 */
			bool setSFXVolume(float volume);


		private:
			AudioManager() = default;

			/**
			 * Key relative to the AssetLoader
			 */
			std::string currentBGM;

			/**
			 * Queue containing the next BGM to play, if any
			 * If the queue is empty, the current BGM will loop
			 * If the queue is not empty, the current BGM will be replaced by the next BGM
			 * The next BGM will be removed from the queue
			 * If the queue is not empty, the next BGM will be played
			 * BGMQueue[0] is the current BGM playing
			 */
			std::vector<std::string> BGMQueue;

			/**
			 * Queue of sound effects to play
			 */
			std::vector<std::string> currentSFX;

			/**
			 * The volume of the background music
			 */
			float BGMVolume = 50.0f;

			/**
			 * The volume of the sound effects
			 */
			float SFXVolume = 50.0f;

			/**
			 * Instance of the AudioManager, lazy loaded
			 */
			static AudioManager _Instance;


	};
} // namespace audio


