/*
** EPITECH PROJECT, 2022
** R-TYPEMIRROR
** File description:
** Buttons
*/

#pragma once

#include "World.hpp"
#include "SFML/Graphics.hpp"

namespace ecs::systems
{
    std::function<void(World &)> menuSelect = [](World &world) {
      auto &positions = world.registry.getComponents<component::Position>();
      auto &drawables = world.registry.getComponents<component::Drawable>();
      auto &sizes = world.registry.getComponents<component::Size>();
      auto mousePosition = sf::Mouse::getPosition(utils::Window::getInstance());
      auto itButton = utils::constant::buttonValueMap.find(utils::constant::PLAY);
      auto itHoveredButton = utils::constant::buttonValueMap.find(utils::constant::PLAY_HOVER);

      for (size_t i = 0; i < positions.size() && i < drawables.size() && i < sizes.size(); i++) {
          auto &pos = positions[i];
          auto &draw = drawables[i];
          auto &size = sizes[i];

          if (draw && pos && size) {
              if ((mousePosition.x >= pos->x && mousePosition.x <= pos->x + size->width) && (mousePosition.y >= pos->y && mousePosition.y <= pos->y + size->height) && draw->IsButton) {
                  draw->rect.top = itButton->second.rectTop + 79;
                  if (draw->rect.left == 324)
                      draw->rect.left = 220;
                  else if (draw->rect.left == 3651)
                      draw->rect.left = 3542;
                  else if (draw->rect.left == 4760)
                      draw->rect.left = 4670;
                  draw->rect.width = itHoveredButton->second.rectWidth;
                  draw->rect.height = itHoveredButton->second.defaultRectHeight;
                  draw->hovered = true;
              } else if (draw->hovered && draw->IsButton){
                  draw->rect.top = itHoveredButton->second.rectTop - 79;
                  if (draw->rect.left == 220)
                      draw->rect.left = 324;
                  else if (draw->rect.left == 3542)
                      draw->rect.left = 3651;
                  else if (draw->rect.left == 4670)
                      draw->rect.left = 4760;
                  draw->rect.width = itButton->second.rectWidth;
                  draw->rect.height = itButton->second.defaultRectHeight;
                  draw->hovered = false;
              }
          }
      }
    };
} // namespace ecs::systems
