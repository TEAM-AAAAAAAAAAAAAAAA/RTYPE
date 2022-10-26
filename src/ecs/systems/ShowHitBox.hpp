/*
** EPITECH PROJECT, by hourcadettej on 10/15/22.
** rtype
** File description:
** rtype
*/

#ifndef RTYPE_SHOWHITBOX_HPP
#define RTYPE_SHOWHITBOX_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"
#include "components/Projectile.hpp"
#include "components/Drawable.hpp"
#include "components/Size.hpp"

#endif // RTYPE_SHOWHITBOX_HPP

namespace ecs::systems
{
    std::function<void(World &)> ShowHitBox = [](World &world) {
      auto const &positions = world.registry.getComponents<component::Position>();
      auto const &drawable = world.registry.getComponents<component::Drawable>();
      auto const &entitySize = world.registry.getComponents<component::Size>();
      sf::RectangleShape hitBox({0, 0});
      hitBox.setFillColor(sf::Color::Transparent);
      hitBox.setOutlineColor(sf::Color::Red);
      hitBox.setOutlineThickness(2);

      for (size_t i = 0; i < positions.size() && i < drawable.size() && entitySize.size(); i++) {
          if (drawable[i] && positions[i] && entitySize[i]) {
              hitBox.setSize({(float)entitySize[i]->width, (float)entitySize[i]->height});
              hitBox.setPosition({(float)(positions[i]->x), (float)(positions[i]->y)});
              world.getWindow().draw(hitBox);
          }
      }
    };
}
