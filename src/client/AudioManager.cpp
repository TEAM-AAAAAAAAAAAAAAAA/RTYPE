/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AudioManager
*/

#include "AudioManager.hpp"
#include "AssetLoader.hpp"

namespace audio
{
    AudioManager &AudioManager::getInstance()
    {
        static AudioManager _Instance;
        return _Instance;
    }

    bool AudioManager::loadBGM(const std::string &key)
    {
        try {
            asset::AssetLoader::GetBGM(getInstance()._currentBGMKey).stop();
            asset::AssetLoader::GetBGM(key).setVolume(getInstance()._BGMVolume);
            asset::AssetLoader::GetBGM(key).setLoop(true);
            asset::AssetLoader::GetBGM(key).play();
            getInstance()._currentBGMKey = key;
        } catch (const std::exception &e) {
            return false;
        }
        return true;
    }

    bool AudioManager::playBGM(bool loop)
    {
        try {
            asset::AssetLoader::GetBGM(getInstance()._currentBGMKey).setLoop(loop);
            asset::AssetLoader::GetBGM(getInstance()._currentBGMKey).play();
        } catch (const std::exception &e) {
            return false;
        }
        return true;
    }

    bool AudioManager::stopBGM()
    {
        try {
            asset::AssetLoader::GetBGM(getInstance()._currentBGMKey).stop();
        } catch (const std::exception &e) {
            return false;
        }
        return true;
    }

    bool AudioManager::setBGMVolume(float volume)
    {
        try {
            asset::AssetLoader::GetBGM(getInstance()._currentBGMKey).setVolume(volume);
            getInstance()._BGMVolume = volume;
        } catch (const std::exception &e) {
            return false;
        }
        return true;
    }

    float AudioManager::getBGMVolume() { return getInstance()._BGMVolume; }

    sf::SoundSource::Status AudioManager::getBGMStatus()
    {
        return asset::AssetLoader::GetBGM(getInstance()._currentBGMKey).getStatus();
    }

    void AudioManager::loopBGM(bool loop)
    {
        try {
            asset::AssetLoader::GetBGM(getInstance()._currentBGMKey).setLoop(loop);
        } catch (const std::exception &e) {
            return;
        }
    }

    void AudioManager::loadSFX(const std::string &key)
    {
        try {
            asset::AssetLoader::GetSFX(key).setVolume(getInstance()._SFXVolume);
            getInstance()._currentSFXKey = key;
        } catch (const std::exception &e) {
            return;
        }
    }

    void AudioManager::playSFX(const std::string &key)
    {
        try {
            asset::AssetLoader::GetSFX(key).setVolume(getInstance()._SFXVolume);
            asset::AssetLoader::GetSFX(key).play();
        } catch (const std::exception &e) {
            return;
        }
    }

    void AudioManager::setSFXVolume(float volume) { getInstance()._SFXVolume = volume; }

    float AudioManager::getSFXVolume() { return getInstance()._SFXVolume; }

}; // namespace audio
