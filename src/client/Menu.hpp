/*
** EPITECH PROJECT, 2022
** R-TYPEMIRROR
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>
#include "AssetLoader.hpp"
#include "Constant.hpp"
#include "Window.hpp"

namespace menu
{
    class Menu {
      public:
        ~Menu() = default;

        static void displayMenu()
        {
            sf::Sprite spritePlayer;
            sf::Sprite spritePlay;
            sf::Sprite spriteOption;
            sf::Sprite spriteQuit;
            int buttonWidth = 600;
            int buttonHeight = 150;

            // utils::Window::get().clear();
            spritePlayer.setTexture(asset::AssetLoader::GetTexture("players"));
            spritePlay.setTexture(asset::AssetLoader::GetTexture("menu"));
            spriteOption.setTexture(asset::AssetLoader::GetTexture("menu"));
            spriteQuit.setTexture(asset::AssetLoader::GetTexture("menu"));
            spritePlayer.setTextureRect(sf::IntRect(1, 1, 32, 16));
            spritePlay.setTextureRect(sf::IntRect(324, 2079, 916, 292));
            spriteOption.setTextureRect(sf::IntRect(3651, 2079, 916, 292));
            spriteQuit.setTextureRect(sf::IntRect(4760, 2079, 916, 292));
            switch (_Instance._currentButtonType) {
                case utils::constant::ButtonType::PLAY:
                    spritePlayer.setPosition((utils::constant::mapWidth / 2 - buttonWidth),
                        (utils::constant::mapHeight / 3) - buttonHeight / 2);
                    break;
                case utils::constant::ButtonType::OPTIONS:
                    spritePlayer.setPosition((utils::constant::mapWidth / 2 - buttonWidth),
                        (utils::constant::mapHeight / 3 + 300) - buttonHeight / 2);
                    break;
                case utils::constant::ButtonType::QUIT:
                    spritePlayer.setPosition((utils::constant::mapWidth / 2 - buttonWidth),
                        (utils::constant::mapHeight / 3 + 500) - buttonHeight / 2);
                    break;
                default: break;
            }
            spritePlayer.setScale(6.f, 6.f);
            spritePlay.setPosition(
                utils::constant::mapWidth / 2 - buttonWidth / 2, (utils::constant::mapHeight / 3) - buttonHeight / 2);
            spritePlay.setScale(static_cast<float>(buttonWidth) / static_cast<float>(spritePlay.getTextureRect().width),
                static_cast<float>(buttonHeight) / static_cast<float>(spritePlay.getTextureRect().height));
            spriteOption.setPosition(utils::constant::mapWidth / 2 - buttonWidth / 2,
                (utils::constant::mapHeight / 3 + 300) - buttonHeight / 2);
            spriteOption.setScale(
                static_cast<float>(buttonWidth) / static_cast<float>(spriteOption.getTextureRect().width),
                static_cast<float>(buttonHeight) / static_cast<float>(spriteOption.getTextureRect().height));
            spriteQuit.setPosition(utils::constant::mapWidth / 2 - buttonWidth / 2,
                (utils::constant::mapHeight / 3 + 500) - buttonHeight / 2);
            spriteQuit.setScale(static_cast<float>(buttonWidth) / static_cast<float>(spriteQuit.getTextureRect().width),
                static_cast<float>(buttonHeight) / static_cast<float>(spriteQuit.getTextureRect().height));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                switch (_Instance._currentButtonType) {
                    case utils::constant::ButtonType::PLAY:
                        _Instance._play = true;
                        break;
                    case utils::constant::ButtonType::OPTIONS:
                        _Instance._options = true;
                        break;
                    case utils::constant::ButtonType::QUIT:
                        _Instance._quit = true;
                        break;
                    default: break;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                switch (_Instance._currentButtonType) {
                    case utils::constant::ButtonType::PLAY:
                        _Instance._currentButtonType = utils::constant::ButtonType::QUIT;
                        break;
                    case utils::constant::ButtonType::OPTIONS:
                        _Instance._currentButtonType = utils::constant::ButtonType::PLAY;
                        break;
                    case utils::constant::ButtonType::QUIT:
                        _Instance._currentButtonType = utils::constant::ButtonType::OPTIONS;
                        break;
                    default: break;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                switch (_Instance._currentButtonType) {
                    case utils::constant::ButtonType::PLAY:
                        _Instance._currentButtonType = utils::constant::ButtonType::OPTIONS;
                        break;
                    case utils::constant::ButtonType::OPTIONS:
                        _Instance._currentButtonType = utils::constant::ButtonType::QUIT;
                        break;
                    case utils::constant::ButtonType::QUIT:
                        _Instance._currentButtonType = utils::constant::ButtonType::PLAY;
                        break;
                    default: break;
                }
            }
            // utils::Window::get().draw(spritePlayer);
            // utils::Window::get().draw(spritePlay);
            // utils::Window::get().draw(spriteOption);
            // utils::Window::get().draw(spriteQuit);

            // utils::Window::get().display();
        }
        static Menu _Instance;

        static inline bool _play;
        static inline bool _options;
        static inline bool _quit;

        utils::constant::ButtonType _currentButtonType = utils::constant::ButtonType::PLAY;
    };
} // namespace menu

#endif /* !MENU_HPP_ */
