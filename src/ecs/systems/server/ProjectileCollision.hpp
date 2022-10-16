#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/Direction.hpp"
#include "components/Weapon.hpp"
#include "components/server/EnemyAI.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/server/Projectile.hpp"

namespace ecs::systems
{
    std::function<void(World &)> projectileCollision = [](World &world) {
        auto const &projectiles = world.registry.getComponents<component::Projectile>();
        auto const &positions = world.registry.getComponents<component::Position>();

#pragma region Proj out of map
        for (size_t i = 0; i < projectiles.size() && i < positions.size(); ++i) {
            auto const &proj = projectiles[i];
            auto const &projPos = positions[i];

            if (proj && projPos) {
                if (projPos.value().x < 0 || projPos.value().x > ecs::constant::mapWidth || projPos.value().y < 0
                    || projPos.value().y > ecs::constant::mapWidth) {
                    world.registry.killEntity(world.registry.entityFromIndex(i));
                }
            }
        };
#pragma endregion

#pragma region Hitreg
        auto &healths = world.registry.getComponents<component::Health>();
        auto const &factions = world.registry.getComponents<component::Faction>();
        auto const &sizes = world.registry.getComponents<component::Size>();
        bool killProj = false;
        size_t projId = 0;

        for (size_t i = 0; i < projectiles.size() && i < positions.size(); ++i) {
            auto const &proj = projectiles[i];
            auto const &projPos = positions[i];

            if (proj && projPos) {
                for (size_t j = 0; j < healths.size() && j < positions.size(); ++j) {
                    auto &victimHealth = healths[j];
                    auto const &victimPos = positions[j];
                    auto const &victimSize = sizes[j];

                    if (victimHealth && victimPos && victimSize) {
                        if (i < factions.size() && j < factions.size())
                            if (factions[i] && factions[j])
                                if (factions[i].value().faction == factions[j].value().faction)
                                    continue;
                        if (projPos.value().x > victimPos.value().x
                            && projPos.value().x < victimPos.value().x + victimSize.value().height
                            && projPos.value().y > victimPos.value().y
                            && projPos.value().x < victimPos.value().y + victimSize.value().height) {
                            victimHealth.value().health -= proj.value().damage;
                            victimHealth.value().health <= 0 ? victimHealth.value().health = 0 : 0;
                            projId = i;
                            killProj = true;
                        }
                    }
                }
            }
        };

        if (killProj)
            world.registry.killEntity(world.registry.entityFromIndex(projId));
#pragma endregion
    };
} // namespace ecs::systems