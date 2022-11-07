/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AudioManager
*/

#include "AudioManager.hpp"
#include "AssetLoader.hpp"

namespace audio {
	AudioManager AudioManager::_Instance;

	bool AudioManager::loadBGM(const std::string &key)
	{
		try {
			asset::AssetLoader::GetBGM(_Instance._currentBGMKey).stop();
			asset::AssetLoader::GetBGM(key).setVolume(_Instance._BGMVolume);
			asset::AssetLoader::GetBGM(key).setLoop(true);
			asset::AssetLoader::GetBGM(key).play();
			_Instance._currentBGMKey = key;
		} catch (const std::exception &e) {
			return false;
		}
		return true;
	}

	bool AudioManager::playBGM(bool loop)
	{
		try {
			asset::AssetLoader::GetBGM(_Instance._currentBGMKey).setLoop(loop);
			asset::AssetLoader::GetBGM(_Instance._currentBGMKey).play();
		} catch (const std::exception &e) {
			return false;
		}
		return true;
	}

	bool AudioManager::stopBGM()
	{
		try {
			asset::AssetLoader::GetBGM(_Instance._currentBGMKey).stop();
		} catch (const std::exception &e) {
			return false;
		}
		return true;
	}

	bool AudioManager::setBGMVolume(float volume)
	{
		try {
			asset::AssetLoader::GetBGM(_Instance._currentBGMKey).setVolume(volume);
			_Instance._BGMVolume = volume;
		} catch (const std::exception &e) {
			return false;
		}
		return true;
	}

	float AudioManager::getBGMVolume()
	{
		return _Instance._BGMVolume;
	}

	sf::SoundSource::Status AudioManager::getBGMStatus()
	{
		return asset::AssetLoader::GetBGM(_Instance._currentBGMKey).getStatus();
	}

	void AudioManager::loopBGM(bool loop)
	{
		try {
			asset::AssetLoader::GetBGM(_Instance._currentBGMKey).setLoop(loop);
		} catch (const std::exception &e) {
			return;
		}
	}

	void AudioManager::loadSFX(const std::string &key)
	{
		try {
			asset::AssetLoader::GetSFX(key).setVolume(_Instance._SFXVolume);
			_Instance._currentSFXKey = key;
		} catch (const std::exception &e) {
			return;
		}
	}

	void AudioManager::playSFX(const std::string &key)
	{
		try {
			asset::AssetLoader::GetSFX(key).play();
		} catch (const std::exception &e) {
			return;
		}
	}

	void AudioManager::setSFXVolume(float volume)
	{
		_Instance._SFXVolume = volume;
	}

	float AudioManager::getSFXVolume()
	{
		return _Instance._SFXVolume;
	}

}; // namespace audio

