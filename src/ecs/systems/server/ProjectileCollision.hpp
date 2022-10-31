#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Direction.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/Weapon.hpp"
#include "components/server/EnemyAI.hpp"
#include "components/server/Projectile.hpp"

namespace ecs::systems
{
    std::function<void(World &)> projectileCollision = [](World &world) {
        auto const &projectiles = world.registry.getComponents<component::Projectile>();
        auto const &positions = world.registry.getComponents<component::Position>();
        auto &healths = world.registry.getComponents<component::Health>();
        auto const &deads = world.registry.getComponents<component::Dead>();

#pragma region Proj out of map
        for (size_t i = 0; i < projectiles.size() && i < positions.size() && i < healths.size(); ++i) {
            if (i < deads.size() && deads[i])
                continue;
            auto const &proj = projectiles[i];
            auto const &projPos = positions[i];
            auto &projHealth = healths[i];

            if (proj && projPos && projHealth) {
                if (projPos.value().x < 0 || projPos.value().x > ecs::constant::mapWidth || projPos.value().y < 0
                    || projPos.value().y > ecs::constant::mapHeight) {
                    projHealth.value().health = 0;
                }
            }
        };
#pragma endregion

#pragma region Hitreg
        auto const &factions = world.registry.getComponents<component::Faction>();
        auto const &sizes = world.registry.getComponents<component::Size>();
        bool killProj = false;
        size_t projId = 0;

        for (size_t i = 0; i < projectiles.size() && i < positions.size() && i < healths.size(); ++i) {
            if (i < deads.size() && deads[i])
                continue;
            auto const &proj = projectiles[i];
            auto const &projPos = positions[i];
            auto &projHealth = healths[i];

            if (proj && projPos && projHealth) {
                for (size_t j = 0; j < healths.size() && j < positions.size(); ++j) {
                    if (j < deads.size() && deads[j])
                        continue;
                    auto &victimHealth = healths[j];
                    auto const &victimPos = positions[j];
                    auto const &victimSize = sizes[j];

                    if (victimHealth && victimPos && victimSize) {
                        if (victimHealth.value().health <= 0)
                            continue;
                        if (i < factions.size() && j < factions.size())
                            if (factions[i] && factions[j])
                                if (factions[i].value().faction == factions[j].value().faction)
                                    continue;
                        if (projPos.value().x > victimPos.value().x
                            && projPos.value().x < victimPos.value().x + victimSize.value().width
                            && projPos.value().y > victimPos.value().y
                            && projPos.value().y < victimPos.value().y + victimSize.value().height) {
                            victimHealth.value().health -= proj.value().damage;
                            victimHealth.value().health <= 0 ? victimHealth.value().health = 0 : 0;
                            projHealth.value().health = 0;
                            break;
                        }
                    }
                }
            }
        };
#pragma endregion
    };
} // namespace ecs::systems
