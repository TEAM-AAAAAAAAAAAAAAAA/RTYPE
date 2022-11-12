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
                  if (!activ->getIsHover())
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
                      default: break;
                  }
                  if (activ->getButtonType() == utils::constant::QUIT_HOVER)
                      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                          utils::Window::getInstance().close();
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
                          default:
                              break;
                      }
                  }
                  activ->setIsHover(false);
              }
          }
      }
    };
} // namespace ecs::systems
