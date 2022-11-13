/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleSFMLEvents
*/

#pragma once

#ifdef WIN32
#include <windows.h>
    #include <shellapi.h>
#endif
#include <functional>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Window.hpp"
#include "World.hpp"
#include "WorldManager.hpp"
#include "../../../client/AudioManager.hpp"

namespace ecs::systems
{
    /**
     * Used to manage Sfml events
     * Currently able to manage the following actions:
     * Close the window
     * KeyPressed, in this case, we check if the bind is known from sfml:
     * if yes, we had it on world's events' stack, nothing otherwise
     */
    std::function<void(World &)> handleSFMLEvents = [](World &world) {
        sf::Event event;
        auto &hitBoxes = world.registry.getComponents<component::Hitbox>();
        auto &controllables = world.registry.getComponents<component::Controllable>();
        auto &activables = world.registry.getComponents<component::Activable>();
        auto &positions = world.registry.getComponents<component::Position>();
        auto &sizes = world.registry.getComponents<component::Size>();
        auto &texts = world.registry.getComponents<component::Text>();
        auto &connections = world.registry.getComponents<component::Connection>();

        while (utils::Window::getInstance().pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: utils::Window::getInstance().close(); break;
                case sf::Event::KeyReleased: {
                    for (size_t i = 0; i < controllables.size(); i++) {
                        auto &contr = controllables[i];

                        if (contr == std::nullopt)
                            continue;
                        if (event.key.code == contr.value().HitBox) {
                            for (size_t j = 0; j < hitBoxes.size(); j++) {
                                auto &hitBox = hitBoxes[j];

                                if (hitBox)
                                    hitBox->switchHitBox();
                            }
                            break;
                        }
                    }
                }
                case sf::Event::MouseButtonReleased: {
                    for (size_t i = 0; i < positions.size() || i < activables.size() || i < sizes.size() || i < connections.size(); i++) {
                        auto mousePosition = sf::Mouse::getPosition(utils::Window::getInstance());

                        if (i < positions.size() && i < sizes.size() && i < activables.size()) {
                            auto &pos = positions[i];
                            auto &activ = activables[i];
                            auto &size = sizes[i];

                            if (pos && size && activ) {
                                if ((mousePosition.x >= pos->x && mousePosition.x <= pos->x + size->width)
                                    && (mousePosition.y >= pos->y && mousePosition.y <= pos->y + size->height)
                                    && activ->getIsButton() && activ->getIsActivate()) {
                                    if (activ->getButtonType() == utils::constant::PLAY_HOVER) {
                                        if (event.mouseButton.button == sf::Mouse::Left) {
                                            network::Message msg;

                                            audio::AudioManager::playSFX("button_click");
                                            msg.fill(0);
                                            msg[0] = 60;
                                            network::Client::getOutgoingMessages().push(msg);
                                            for (size_t j = 0; j < activables.size(); j++) {
                                                if (j < connections.size())
                                                    if (connections[j])
                                                        connections[j]->setIsSet(false);
                                                if (activables[j]->getButtonType() == utils::constant::ROOM
                                                    || activables[j]->getButtonType() == utils::constant::ROOM_TEXT
                                                    || activables[j]->getButtonType() == utils::constant::PLANET) {
                                                    activables[j]->switchSetIsActivate();
                                                }
                                            }
                                            for (size_t j = 0; j < activables.size() && j < texts.size(); j++)
                                                if (activables[j]->getButtonType() == utils::constant::ROOM_TEXT)
                                                    texts[j]->setIsSet(false);
                                        }
                                    } else if (activ->getButtonType() == utils::constant::ROOM_HOVER) {
                                        if (i < connections.size()) {
                                            auto &connec = connections[i];

                                            if (connec) {
                                                if (event.mouseButton.button == sf::Mouse::Left) {
                                                    auto port = connec->getPort();
                                                    auto host = connec->getHost();
                                                    audio::AudioManager::playSFX("button_click");
                                                    connec->setClientConnection();
                                                    ecs::WorldManager::setWaitingWorld([] { return getGameWorld(); });
                                                }
                                            }
                                        }
                                    } else if (activ->getButtonType() == utils::constant::HOW_TO_HOVER) {
                                        if (event.mouseButton.button == sf::Mouse::Left) {
#ifdef WIN32
                                            ShellExecute(0, 0, "https://cavonstavants-organization.gitbook.io/rtype/how-to-play", 0, 0 , SW_SHOW );
#else
                                            std::string url = "https://cavonstavants-organization.gitbook.io/rtype/how-to-play";
                                            system(std::string("xdg-open " + url).c_str());
#endif
                                        }

                                    } else if (activ->getButtonType() == utils::constant::OPTION_HOVER) {
                                        if (event.mouseButton.button == sf::Mouse::Left) {
                                            audio::AudioManager::playSFX("button_click");
                                            for (size_t j = 0; j < activables.size() && texts.size(); j++)
                                                if (activables[j]->getButtonType() == utils::constant::OPTION_INTERFACE
                                                    || activables[j]->getButtonType() == utils::constant::SOUND_LEFT
                                                    || activables[j]->getButtonType() == utils::constant::SOUND_RIGHT
                                                    || activables[j]->getButtonType() == utils::constant::HOW_TO
                                                    || activables[j]->getButtonType() == utils::constant::SLIDE_MUSIC
                                                    || activables[j]->getButtonType() == utils::constant::SLIDE_SOUND
                                                    || activables[j]->getButtonType() == utils::constant::SOUND_BAR
                                                    || activables[j]->getButtonType() == utils::constant::SETTINGS
                                                    || activables[j]->getButtonType() == utils::constant::OPTIONS_TEXT
                                                    || activables[j]->getButtonType() == utils::constant::MUSIC_LEFT
                                                    || activables[j]->getButtonType() == utils::constant::MUSIC_RIGHT) {
                                                    activables[j]->switchSetIsActivate();
                                                }
                                        }
                                    } else if (activ->getButtonType() == utils::constant::SOUND_LEFT_HOVER ||
                                               activ->getButtonType() == utils::constant::SOUND_RIGHT_HOVER) {
                                        if (event.mouseButton.button == sf::Mouse::Left) {
                                            audio::AudioManager::playSFX("button_click");
                                            for (size_t j = 0; j < activables.size() || j < positions.size(); j++) {
                                                if (!positions[j] || !activables[j])
                                                    continue;
                                                if (activables[j]->getButtonType() == utils::constant::SLIDE_SOUND) {
                                                    auto sound = audio::AudioManager::getSFXVolume();
                                                    if (activ->getButtonType() == utils::constant::SOUND_LEFT_HOVER) {
                                                        if (positions[j]->x > 903) {
                                                            audio::AudioManager::setSFXVolume(sound - 5);
                                                            positions[j]->x -= 17;
                                                        }
                                                    } else {
                                                        if (positions[j]->x < 1213) {
                                                            audio::AudioManager::setSFXVolume(sound + 5);
                                                            positions[j]->x += 17;
                                                        }
                                                    }
                                                }
                                            }

                                        }
                                    } else if (activ->getButtonType() == utils::constant::MUSIC_LEFT_HOVER ||
                                               activ->getButtonType() == utils::constant::MUSIC_RIGHT_HOVER) {
                                        if (event.mouseButton.button == sf::Mouse::Left) {
                                            audio::AudioManager::playSFX("button_click");
                                            for (size_t j = 0; j < activables.size() || j < positions.size(); j++) {
                                                if (!positions[j] || !activables[j])
                                                    continue;
                                                if (activables[j]->getButtonType() == utils::constant::SLIDE_MUSIC) {
                                                    auto music = audio::AudioManager::getBGMVolume();
                                                    if (activ->getButtonType() == utils::constant::MUSIC_LEFT_HOVER) {
                                                        if (positions[j]->x > 903) {
                                                            audio::AudioManager::setBGMVolume(music - 5);
                                                            positions[j]->x -= 17;
                                                        }
                                                    } else {
                                                        if (positions[j]->x < 1213) {
                                                            audio::AudioManager::setBGMVolume(music + 5);
                                                            positions[j]->x += 17;
                                                        }
                                                    }
                                                }
                                            }

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                default: break;
            }
        }
    };
} // namespace ecs::systems
