/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleSFMLEvents
*/

#pragma once

#include <functional>
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
                  for (size_t i = 0; i < positions.size() && i < activables.size() && i < sizes.size(); i++) {
                      auto &pos = positions[i];
                      auto &activ = activables[i];
                      auto &size = sizes[i];
                      auto &text = texts[i];
                      auto mousePosition = sf::Mouse::getPosition(utils::Window::getInstance());

                      if (pos && size && activ) {
                          if ((mousePosition.x >= pos->x && mousePosition.x <= pos->x + size->width)
                              && (mousePosition.y >= pos->y && mousePosition.y <= pos->y + size->height)
                              && activ->getIsButton()) {
                              audio::AudioManager::playSFX("button_click");
                              if (activ->getButtonType() == utils::constant::PLAY_HOVER)
                                  if (event.mouseButton.button == sf::Mouse::Left) {
                                      for (size_t j = 0; j < activables.size() && texts.size(); j++)
                                          if (activables[j]->getButtonType() == utils::constant::ROOM
                                              || activables[j]->getButtonType() == utils::constant::ROOM_TEXT) {
                                              activables[j]->switchSetIsActivate();
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
