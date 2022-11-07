#include "AttackAI.hpp"
#include "WorldManager.hpp"
#include "components/Direction.hpp"
#include "components/EntityType.hpp"
#include "components/Faction.hpp"
#include "components/NetworkId.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/server/Projectile.hpp"

namespace ecs::component
{
    void AttackAI::Action::shootBulletAttack(const std::size_t shooter)
    {
        // auto const &positions = ecs::WorldManager::getWorld().registry.getComponents<component::Position>();
        // auto const &factions = ecs::WorldManager::getWorld().registry.getComponents<component::Faction>();

        // if (!(shooter < positions.size()))
        //     return;
        // if (!(positions[shooter]))
        //     return;
        // ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        // if (shooter < factions.size() && factions[shooter])
        //     fac = factions[shooter].value().faction;
        // spawnNewBullet(component::EntityType::Bullet, positions[shooter].value().x, positions[shooter].value().y, -1,
        // 0, 20, 20, 10, 0, 10, fac);
    }

    void AttackAI::Action::shootEnerySphereAttack(const std::size_t shooter)
    {
        // auto const &positions = ecs::WorldManager::getWorld().registry.getComponents<component::Position>();
        // auto const &factions = ecs::WorldManager::getWorld().registry.getComponents<component::Faction>();

        // if (!(shooter < positions.size()))
        //     return;
        // if (!(positions[shooter]))
        //     return;
        // ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        // if (shooter < factions.size() && factions[shooter])
        //     fac = factions[shooter].value().faction;
        // spawnNewBullet(component::EntityType::EnergySphere, positions[shooter].value().x,
        // positions[shooter].value().y,
        //     -1, 0, 50, 50, 5, 0, 50, fac);
    }

    void AttackAI::Action::spawnNewBullet(component::EntityType::Types type, int posX, int posY, char dirX, char dirY,
        int sizeX, int sizeY, int velX, int velY, int dmg, ecs::component::Faction::Factions fac)
    {
        ecs::Entity bullet = ecs::WorldManager::getWorld().registry.spawn_entity();
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::EntityType>(bullet, {type});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::NetworkId>(
            bullet, {static_cast<size_t>(bullet)});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Position>(bullet, {posX, posY});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Direction>(bullet, {dirX, dirY});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Size>(bullet, {sizeX, sizeY});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Velocity>(bullet, {velX, velY});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Projectile>(bullet, {dmg});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Faction>(bullet, {fac});
    }

    const std::unordered_map<AttackAI::PatternType, AttackAI::AI::Pattern> AttackAI::AI::patterns(
        {{ShootBullet, {200, AttackAI::Action::shootBulletAttack}},
            {ShootEnergySphere, {300, AttackAI::Action::shootEnerySphereAttack}}});

    const std::unordered_map<AttackAI::AIType, AttackAI::AI> AttackAI::_aiVector(
        {{Scout, AttackAI::AI({ShootBullet})}, {Fighter, AttackAI::AI({ShootBullet, ShootEnergySphere})}});
} // namespace ecs::component
