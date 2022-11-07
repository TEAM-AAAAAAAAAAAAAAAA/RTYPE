#include "AttackAI.hpp"
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
    void AttackAI::Action::shootBulletAttack(World &world, const std::size_t &shooter)
    {
        auto const &positions = world.registry.getComponents<component::Position>();
        auto const &factions = world.registry.getComponents<component::Faction>();

        if (!(shooter < positions.size()))
            return;
        if (!(positions[shooter]))
            return;
        ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        if (shooter < factions.size() && factions[shooter])
            fac = factions[shooter].value().faction;
        spawnNewBullet(world, component::EntityType::Bullet, positions[shooter].value().x, positions[shooter].value().y,
            -1, 0, 20, 20, 10, 0, 10, fac);
    }

    void AttackAI::Action::shootEneryBallsAttack(World &world, const std::size_t &shooter)
    {
        auto const &positions = world.registry.getComponents<component::Position>();
        auto const &factions = world.registry.getComponents<component::Faction>();

        if (!(shooter < positions.size()))
            return;
        if (!(positions[shooter]))
            return;
        ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        if (shooter < factions.size() && factions[shooter])
            fac = factions[shooter].value().faction;
        spawnNewBullet(world, component::EntityType::EnergySphere, positions[shooter].value().x,
            positions[shooter].value().y, -1, 0, 50, 50, 5, 0, 50, fac);
    }

    void AttackAI::Action::spawnNewBullet(World &world, component::EntityType::Types type, int posX, int posY,
        char dirX, char dirY, int sizeX, int sizeY, int velX, int velY, int dmg, ecs::component::Faction::Factions fac)
    {
        ecs::Entity bullet = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::EntityType>(bullet, {type});
        world.registry.addComponent<ecs::component::NetworkId>(bullet, {static_cast<size_t>(bullet)});
        world.registry.addComponent<ecs::component::Position>(bullet, {posX, posY});
        world.registry.addComponent<ecs::component::Direction>(bullet, {dirX, dirY});
        world.registry.addComponent<ecs::component::Size>(bullet, {sizeX, sizeY});
        world.registry.addComponent<ecs::component::Velocity>(bullet, {velX, velY});
        world.registry.addComponent<ecs::component::Projectile>(bullet, {dmg});
        world.registry.addComponent<ecs::component::Faction>(bullet, {fac});
    }

    const std::unordered_map<AttackAI::PatternType, AttackAI::AI::Pattern> AttackAI::AI::patterns({
        {ShootBullet, {200, AttackAI::Action::shootBulletAttack}},
        {ShootEnergySphere, {300, AttackAI::Action::shootEneryBallsAttack}}
    });

    const std::unordered_map<AttackAI::AIType, AttackAI::AI> AttackAI::_aiVector(
        {{Scout, AttackAI::AI({ShootBullet})}, {Fighter, AttackAI::AI({ShootBullet, ShootEnergySphere})}});
} // namespace ecs::component
