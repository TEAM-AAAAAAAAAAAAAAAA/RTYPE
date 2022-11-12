/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Draw
*/

#pragma once

#include <functional>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/client/Animated.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Hitbox.hpp"
#include "components/client/Text.hpp"

namespace ecs::systems
{
    /**
     * Used to set the scale, the position and the texture of the entity before display it
     */
    std::function<void(World &)> draw = [](World &world) {
      auto const &positions = world.registry.getComponents<component::Position>();
      auto const &sizes = world.registry.getComponents<component::Size>();
      auto const &drawables = world.registry.getComponents<component::Drawable>();
      auto const &animations = world.registry.getComponents<component::Animated>();
      auto const &hitBoxes = world.registry.getComponents<component::Hitbox>();
      auto const &texts = world.registry.getComponents<component::Text>();
      auto const &activables = world.registry.getComponents<component::Activable>();

      utils::Window::getInstance().clear(utils::Window::Color);
      for (size_t i = 0; i < positions.size()
           || i < sizes.size() || i < drawables.size()
           || i < animations.size() || i < hitBoxes.size()
           || i < texts.size() || i < activables.size(); i++) {
          if (i < drawables.size() && i < activables.size() && i < positions.size() && i < sizes.size()) {
              auto const &draw = drawables[i];
              auto const &activ = activables[i];
              auto const &pos = positions[i];
              auto const &size = sizes[i];
#pragma region texture
              if (pos && size && draw && activ) {
                  if (activ->getIsActivate()) {
                      sf::Sprite sprite;
                      sprite.setTexture(draw.value().getTexture());
                      if (i < animations.size() && animations[i]) {
                          sprite.setTextureRect(animations[i].value().getFrameRect());
                      } else {
                          sprite.setTextureRect(draw.value().rect);
                      }
                      float scaleX =
                          static_cast<float>(size.value().width) / static_cast<float>(sprite.getTextureRect().width);
                      float scaleY =
                          static_cast<float>(size.value().height) / static_cast<float>(sprite.getTextureRect().height);
                      sprite.setScale(scaleX, scaleY);
                      sprite.setPosition({static_cast<float>(pos.value().x), static_cast<float>(pos.value().y)});
                      utils::Window::getInstance().draw(sprite);
                  }
              }
          }
#pragma endregion

#pragma region text
          if (i < texts.size() && i < positions.size() && i < sizes.size() && i < activables.size()) {
              auto const &text = texts[i];
              auto const &activ = activables[i];
              auto const &pos = positions[i];
              auto const &size = sizes[i];

              if (text && activ && size && pos) {
                  for (size_t j = 0; j < text->getContentSize(); j++) {
                      if (activ->getIsActivate() && !text->getContent(j).empty()) {
                          sf::Text sfText;
                          sf::Color textColor;
                          size_t textLength = 0;

                          textColor.r = text->getTextColor().r;
                          textColor.g = text->getTextColor().g;
                          textColor.b = text->getTextColor().b;
                          textColor.a = text->getTextColor().a;
                          sfText.setCharacterSize(size->height);
                          sfText.setFont(text->getFont());
                          (j > 0) ? textLength = text->getContent(j - 1).length() : 0;
                          sfText.setPosition(
                              static_cast<float>(pos->x + j * size->height + textLength * size->width), static_cast<float>(pos->y));
                          sfText.setFillColor(textColor);
                          sfText.setString(text->getContent(j));
                          utils::Window::getInstance().draw(sfText);
                      }
                  }
              }
          }
#pragma endregion
#pragma region hitbox
          if (i < hitBoxes.size() && i < positions.size() && i < sizes.size()) {
              auto const &hitBox = hitBoxes[i];
              auto const &pos = positions[i];
              auto const &size = sizes[i];

              if (hitBox && size && pos) {
                  if (hitBox->enableHitBox) {
                      sf::RectangleShape hitBoxRec({0, 0});

                      hitBoxRec.setFillColor(sf::Color::Transparent);
                      hitBoxRec.setOutlineColor(sf::Color::Red);
                      hitBoxRec.setOutlineThickness(2);
                      hitBoxRec.setSize({(float)size->width, (float)size->height});
                      hitBoxRec.setPosition({(float)(pos->x), (float)(pos->y)});
                      utils::Window::getInstance().draw(hitBoxRec);
                  }
              }
          }
      };
#pragma endregion
      utils::Window::getInstance().display();
    };
} // namespace ecs::systems
