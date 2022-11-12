/*
** EPITECH PROJECT, 2022
** R-TYPEMIRROR
** File description:
** Buttons
*/

#pragma once

#include "World.hpp"
#include "SFML/Graphics.hpp"
#include "../../../client/GetWorld.hpp"
#include "../../../client/AudioManager.hpp"

namespace ecs::systems
{
    std::function<void(World &)> menuSelect = [](World &world) {
      auto &positions = world.registry.getComponents<component::Position>();
      auto &drawables = world.registry.getComponents<component::Drawable>();
      auto &sizes = world.registry.getComponents<component::Size>();
      auto &activables = world.registry.getComponents<component::Activable>();
      auto mousePosition = sf::Mouse::getPosition(utils::Window::getInstance());
      auto itButton = utils::constant::buttonValueMap.find(utils::constant::PLAY);
      auto itButtonRoom = utils::constant::buttonValueMap.find(utils::constant::ROOM);
      auto itHoveredButton = utils::constant::buttonValueMap.find(utils::constant::PLAY_HOVER);

      for (size_t i = 0; i < positions.size() && i < drawables.size() && i < sizes.size(); i++) {
          auto &pos = positions[i];
          auto &draw = drawables[i];
          auto &size = sizes[i];
          auto &activ = activables[i];

          if (draw && pos && size && activ) {
              if ((mousePosition.x >= pos->x && mousePosition.x <= pos->x + size->width) && (mousePosition.y >= pos->y && mousePosition.y <= pos->y + size->height) && activ->getIsButton()) {
                  if (!activ->getIsHover() && activ->getIsActivate())
                      audio::AudioManager::playSFX("button_hover");
                  switch(activ->getButtonType()) {
                      case utils::constant::PLAY: {
                          activ->setButtonType(utils::constant::PLAY_HOVER);
                          draw->rect.top = itHoveredButton->second.rectTop;
                          draw->rect.left = 220;
                          draw->rect.width = itHoveredButton->second.defaultRectWidth;
                          draw->rect.height = itHoveredButton->second.defaultRectHeight;
                          break;
                      }
                      case utils::constant::OPTION: {
                          activ->setButtonType(utils::constant::OPTION_HOVER);
                          draw->rect.top = itHoveredButton->second.rectTop;
                          draw->rect.left = 3542;
                          draw->rect.width = itHoveredButton->second.defaultRectWidth;
                          draw->rect.height = itHoveredButton->second.defaultRectHeight;
                          break;
                      }
                      case utils::constant::QUIT: {
                          activ->setButtonType(utils::constant::QUIT_HOVER);
                          draw->rect.top = itHoveredButton->second.rectTop;
                          draw->rect.left = 4670;
                          draw->rect.width = itHoveredButton->second.defaultRectWidth;
                          draw->rect.height = itHoveredButton->second.defaultRectHeight;
                          break;
                      }
                      case utils::constant::ROOM: {
                          activ->setButtonType(utils::constant::ROOM_HOVER);
                          draw->rect.top = 1510;
                          draw->rect.width = itHoveredButton->second.defaultRectWidth;
                          draw->rect.height = itHoveredButton->second.defaultRectHeight;
                          break;
                      }
                      case utils::constant::SOUND_LEFT: {
                          auto itLeft = utils::constant::buttonValueMap.find(utils::constant::SOUND_LEFT_HOVER);
                          activ->setButtonType(utils::constant::SOUND_LEFT_HOVER);
                          draw->rect.top = itLeft->second.rectTop;
                          draw->rect.left = itLeft->second.rectLeft;
                          break;
                      }
                      case utils::constant::SOUND_RIGHT: {
                          auto itRight = utils::constant::buttonValueMap.find(utils::constant::SOUND_RIGHT_HOVER);
                          activ->setButtonType(utils::constant::SOUND_RIGHT_HOVER);
                          draw->rect.top = itRight->second.rectTop;
                          draw->rect.left = itRight->second.rectLeft;
                          break;
                      }
                      case utils::constant::MUSIC_LEFT: {
                          auto itLeft = utils::constant::buttonValueMap.find(utils::constant::MUSIC_LEFT_HOVER);
                          activ->setButtonType(utils::constant::MUSIC_LEFT_HOVER);
                          draw->rect.top = itLeft->second.rectTop;
                          draw->rect.left = itLeft->second.rectLeft;
                          break;
                      }
                      case utils::constant::MUSIC_RIGHT: {
                          auto itRight = utils::constant::buttonValueMap.find(utils::constant::MUSIC_RIGHT_HOVER);
                          activ->setButtonType(utils::constant::MUSIC_RIGHT_HOVER);
                          draw->rect.top = itRight->second.rectTop;
                          draw->rect.left = itRight->second.rectLeft;
                          break;
                      }
                      case utils::constant::HOW_TO: {
                          auto itHowTo = utils::constant::buttonValueMap.find(utils::constant::HOW_TO_HOVER);
                          activ->setButtonType(utils::constant::HOW_TO_HOVER);
                          draw->rect.top = itHowTo->second.rectTop;
                          draw->rect.left = itHowTo->second.rectLeft;
                          break;
                      }
                      case utils::constant::SETTINGS: {
                          auto itSettings = utils::constant::buttonValueMap.find(utils::constant::SETTINGS_HOVER);
                          activ->setButtonType(utils::constant::SETTINGS_HOVER);
                          draw->rect.top = itSettings->second.rectTop;
                          draw->rect.left = itSettings->second.rectLeft;
                          break;
                      }
                      default: break;
                  }
                  activ->setIsHover(true);
              } else if (activ->getIsHover() && activ->getIsButton()){
                  activ->getButtonType() == utils::constant::ROOM ? draw->rect.top = itButtonRoom->second.rectTop : 0;
                  switch(activ->getButtonType()) {
                      case utils::constant::PLAY_HOVER: {
                          activ->setButtonType(utils::constant::PLAY);
                          draw->rect.left = 324;
                          draw->rect.top = itButton->second.rectTop;
                          draw->rect.width = itButton->second.defaultRectWidth;
                          draw->rect.height = itButton->second.defaultRectHeight;
                          break;
                      }
                      case utils::constant::OPTION_HOVER: {
                          activ->setButtonType(utils::constant::OPTION);
                          draw->rect.left = 3651;
                          draw->rect.top = itButton->second.rectTop;
                          draw->rect.width = itButton->second.defaultRectWidth;
                          draw->rect.height = itButton->second.defaultRectHeight;
                          break;
                      }
                      case utils::constant::QUIT_HOVER: {
                          if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                              utils::Window::getInstance().close();
                          activ->setButtonType(utils::constant::QUIT);
                          draw->rect.left = 4760;
                          draw->rect.top = itButton->second.rectTop;
                          draw->rect.width = itButton->second.defaultRectWidth;
                          draw->rect.height = itButton->second.defaultRectHeight;
                          break;
                      }
                      case utils::constant::ROOM_HOVER: {
                          activ->setButtonType(utils::constant::ROOM);
                          draw->rect.top = 456;
                          draw->rect.width = itButtonRoom->second.defaultRectWidth;
                          draw->rect.height = itButtonRoom->second.defaultRectHeight;
                          break;
                      }
                      case utils::constant::SOUND_LEFT_HOVER: {
                          auto itLeft = utils::constant::buttonValueMap.find(utils::constant::SOUND_LEFT);
                          activ->setButtonType(utils::constant::SOUND_LEFT);
                          draw->rect.top = itLeft->second.rectTop;
                          draw->rect.left = itLeft->second.rectLeft;
                          break;
                      }
                      case utils::constant::SOUND_RIGHT_HOVER: {
                          auto itRight = utils::constant::buttonValueMap.find(utils::constant::SOUND_RIGHT);
                          activ->setButtonType(utils::constant::SOUND_RIGHT);
                          draw->rect.top = itRight->second.rectTop;
                          draw->rect.left = itRight->second.rectLeft;
                          break;
                      }
                      case utils::constant::MUSIC_LEFT_HOVER: {
                          auto itLeft = utils::constant::buttonValueMap.find(utils::constant::MUSIC_LEFT);
                          activ->setButtonType(utils::constant::MUSIC_LEFT);
                          draw->rect.top = itLeft->second.rectTop;
                          draw->rect.left = itLeft->second.rectLeft;
                          break;
                      }
                      case utils::constant::MUSIC_RIGHT_HOVER: {
                          auto itRight = utils::constant::buttonValueMap.find(utils::constant::MUSIC_RIGHT);
                          activ->setButtonType(utils::constant::MUSIC_RIGHT);
                          draw->rect.top = itRight->second.rectTop;
                          draw->rect.left = itRight->second.rectLeft;
                          break;
                      }
                      case utils::constant::HOW_TO_HOVER: {
                          auto itHowTo = utils::constant::buttonValueMap.find(utils::constant::HOW_TO);
                          activ->setButtonType(utils::constant::HOW_TO);
                          draw->rect.top = itHowTo->second.rectTop;
                          draw->rect.left = itHowTo->second.rectLeft;
                          break;
                      }
                      case utils::constant::SETTINGS_HOVER: {
                          auto itSettings = utils::constant::buttonValueMap.find(utils::constant::SETTINGS);
                          activ->setButtonType(utils::constant::SETTINGS);
                          draw->rect.top = itSettings->second.rectTop;
                          draw->rect.left = itSettings->second.rectLeft;
                          break;
                      }
                      default:
                          break;
                  }
                  activ->setIsHover(false);
              }
          }
      }
    };
} // namespace ecs::systems
