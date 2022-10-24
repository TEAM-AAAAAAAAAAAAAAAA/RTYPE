#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/Projectile.hpp"

namespace ecs::systems
{
    std::function<void(World &)> projectileCollision = [](World &world) {
      auto const &projectiles = world.registry.getComponents<component::Projectile>();
      auto const &positions = world.registry.getComponents<component::Position>();
      auto &healths = world.registry.getComponents<component::Health>();
      auto const &sizes = world.registry.getComponents<component::Size>();
      std::stack<size_t> entities_to_kill;

      if (!projectiles.size() || !positions.size() || !healths.size() || !sizes.size())
          return;
      for (size_t i = 0; i < projectiles.size() && i < positions.size(); i++) {
          auto const &proj = projectiles[i];
          auto const &projPos = positions[i];

          if (!proj || !projPos)
              continue;
          for (size_t j = 0; j < healths.size() && j < positions.size() && j < sizes.size(); j++) {
              auto &victimHealth = healths[j];
              auto const &victimPos = positions[j];
              auto const &victimSize = sizes[j];

              if (victimHealth && victimPos && victimSize) {
                  if (projPos.value().x > victimPos.value().x
                      && projPos.value().x < victimPos.value().x + victimSize.value().width
                      && projPos.value().y > victimPos.value().y
                      && projPos.value().x < victimPos.value().y + victimSize.value().height) {
                      victimHealth.value().health -= proj.value().damage;
                      if (victimHealth.value().health <= 0)
                          entities_to_kill.push(j);
                      entities_to_kill.push(i);
                  }
              }
          }
          if (projPos.value().x < 0
              || projPos.value().x > ecs::constant::mapWidth
              || projPos.value().y < 0
              || projPos.value().y > ecs::constant::mapHeight) {
              std::cout << "KILL PROJ pos.x : " << projPos.value().x << " | pos.y : " << projPos.value().y << std::endl;
              entities_to_kill.push(i);
          }
      }
      while (!entities_to_kill.empty()) {
//            std::cout << "bin size : " << entities_to_kill.size() << " | id : " << entities_to_kill.top() << std::endl;
          world.registry.killEntity(world.registry.entityFromIndex(entities_to_kill.top()));
          entities_to_kill.pop();
      }
//        std::cout << "[END] bin size : " << entities_to_kill.size() << std::endl;
    };
} // namespace ecs::systems
