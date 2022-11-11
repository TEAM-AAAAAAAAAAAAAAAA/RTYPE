#include "AttackAI.hpp"
#include "EnemyFactory.hpp"
#include "WorldManager.hpp"
#include "components/Direction.hpp"
#include "components/EntityType.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/NetworkId.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/server/Projectile.hpp"

namespace ecs::component
{
    void AttackAI::Action::spawnNewBullet(component::EntityType::Types type, int posX, int posY, char dirX, char dirY,
        int sizeX, int sizeY, int velX, int velY, int dmg, ecs::component::Faction::Factions fac, int bulletHealth)
    {
        ecs::Entity bullet = ecs::WorldManager::getWorld().registry.spawn_entity();
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::EntityType>(
            bullet, {static_cast<char>(type)});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::NetworkId>(
            bullet, {static_cast<size_t>(bullet)});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Position>(bullet, {posX, posY});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Direction>(bullet, {dirX, dirY});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Size>(bullet, {sizeX, sizeY});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Velocity>(bullet, {velX, velY});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Projectile>(bullet, {dmg});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Faction>(bullet, {fac});
        ecs::WorldManager::getWorld().registry.addComponent<ecs::component::Health>(bullet, {bulletHealth});
    }

    void AttackAI::Action::waitAttack(const std::size_t shooter) {}

    void AttackAI::Action::shootBulletAttack(const std::size_t shooter)
    {
        auto const &positions = ecs::WorldManager::getWorld().registry.getComponents<component::Position>();
        auto const &factions = ecs::WorldManager::getWorld().registry.getComponents<component::Faction>();

        if (!(shooter < positions.size()))
            return;
        if (!(positions[shooter]))
            return;
        ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        if (shooter < factions.size() && factions[shooter])
            fac = factions[shooter].value().faction;
        AttackAI::Action::spawnNewBullet(component::EntityType::Bullet, positions[shooter].value().x,
            positions[shooter].value().y, -1, 0, 20, 20, 10, 0, 10, fac);
    }

    void AttackAI::Action::shootEnerySphereAttack(const std::size_t shooter)
    {
        auto const &positions = ecs::WorldManager::getWorld().registry.getComponents<component::Position>();
        auto const &factions = ecs::WorldManager::getWorld().registry.getComponents<component::Faction>();

        if (!(shooter < positions.size()))
            return;
        if (!(positions[shooter]))
            return;
        ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        if (shooter < factions.size() && factions[shooter])
            fac = factions[shooter].value().faction;
        spawnNewBullet(component::EntityType::EnergySphere, positions[shooter].value().x, positions[shooter].value().y,
            -1, 0, 50, 50, 5, 0, 50, fac);
    }

    void AttackAI::Action::shootLaserAttack(const std::size_t shooter)
    {
        auto const &positions = ecs::WorldManager::getWorld().registry.getComponents<component::Position>();
        auto const &factions = ecs::WorldManager::getWorld().registry.getComponents<component::Faction>();

        if (!(shooter < positions.size()))
            return;
        if (!(positions[shooter]))
            return;
        ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        if (shooter < factions.size() && factions[shooter])
            fac = factions[shooter].value().faction;
        AttackAI::Action::spawnNewBullet(component::EntityType::Laser, positions[shooter].value().x,
            positions[shooter].value().y, -1, 0, 6, 32, 15, 0, 5, fac);
    }

    void AttackAI::Action::shootRocketAttack(const std::size_t shooter)
    {
        auto const &positions = ecs::WorldManager::getWorld().registry.getComponents<component::Position>();
        auto const &factions = ecs::WorldManager::getWorld().registry.getComponents<component::Faction>();

        if (!(shooter < positions.size()))
            return;
        if (!(positions[shooter]))
            return;
        ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        if (shooter < factions.size() && factions[shooter])
            fac = factions[shooter].value().faction;
        AttackAI::Action::spawnNewBullet(component::EntityType::Rocket, positions[shooter].value().x,
            positions[shooter].value().y, -1, 0, 30, 20, 15, 0, 25, fac);
    }

    void AttackAI::Action::invokeAlliesAttack(const std::size_t shooter)
    {
        auto const &positions = ecs::WorldManager::getWorld().registry.getComponents<component::Position>();
        auto const &factions = ecs::WorldManager::getWorld().registry.getComponents<component::Faction>();

        if (!(shooter < positions.size() && shooter < factions.size()))
            return;
        if (!(positions[shooter] && factions[shooter]))
            return;

        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x - 75, positions[shooter].value().y - 75, factions[shooter].value().faction,
            MovementAI::AIType::ClockwiseSmall);
        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x, positions[shooter].value().y - 50, factions[shooter].value().faction,
            MovementAI::AIType::ClockwiseBig);
        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x + 50, positions[shooter].value().y + 50, factions[shooter].value().faction,
            MovementAI::AIType::AntiClockwiseSmall);
        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x + 50, positions[shooter].value().y - 75, factions[shooter].value().faction,
            MovementAI::AIType::AntiClockwiseBig);
    }

    void AttackAI::Action::spawnAsteroidsAttack(const std::size_t shooter)
    {
        auto const &factions = ecs::WorldManager::getWorld().registry.getComponents<component::Faction>();

        ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
        if (shooter < factions.size() && factions[shooter])
            fac = factions[shooter].value().faction;
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
        AttackAI::Action::spawnNewBullet(component::EntityType::Asteroid, 400 + std::rand() % utils::constant::mapWidth,
            ((-utils::constant::mapHeight) / 2) + std::rand() % (utils::constant::mapHeight / 2), -1, 1, 100, 100, 10,
            10, 10, fac, 500);
    }

    void AttackAI::Action::invokeAnyoneAttack(const std::size_t shooter)
    {
        auto const &positions = ecs::WorldManager::getWorld().registry.getComponents<component::Position>();

        if (!(shooter < positions.size()))
            return;
        if (!(positions[shooter]))
            return;

        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x - 100, positions[shooter].value().y + 50, Faction::Factions::Uranus,
            MovementAI::AIType::LongUpDown);
        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x - 100, positions[shooter].value().y + 100, Faction::Factions::Janitor,
            MovementAI::AIType::LongUpDown);
        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x - 100, positions[shooter].value().y + 150, Faction::Factions::Alien,
            MovementAI::AIType::LongUpDown);
        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x - 100, positions[shooter].value().y + 200, Faction::Factions::Uranus,
            MovementAI::AIType::LongUpDown);
        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x - 100, positions[shooter].value().y + 250, Faction::Factions::Janitor,
            MovementAI::AIType::LongUpDown);
        ecs::EnemyFactory::spawnEnemy(ecs::WorldManager::getWorld(), ecs::EnemyFactory::EnemyType::Fighter,
            positions[shooter].value().x - 100, positions[shooter].value().y + 300, Faction::Factions::Alien,
            MovementAI::AIType::LongUpDown);
    }

    const std::unordered_map<AttackAI::PatternType, AttackAI::AI::Pattern> AttackAI::AI::patterns(
        {{Wait, AI::Pattern(1000, AttackAI::Action::waitAttack)},
            {WaitShort, AI::Pattern(500, AttackAI::Action::waitAttack)},
            {WaitLong, AI::Pattern(2000, AttackAI::Action::waitAttack)},
            {ShootBullet, AI::Pattern(250, AttackAI::Action::shootBulletAttack)},
            {ShootEnergySphere, AI::Pattern(500, AttackAI::Action::shootEnerySphereAttack)},
            {ShootEnergySphereFast, AI::Pattern(10, AttackAI::Action::shootEnerySphereAttack)},
            {ShootLaser, AI::Pattern(50, AttackAI::Action::shootLaserAttack)},
            {ShootRocket, AI::Pattern(350, AttackAI::Action::shootRocketAttack)},
            {InvokeAllies, AI::Pattern(2500, AttackAI::Action::invokeAlliesAttack)},
            {InvokeAnyone, AI::Pattern(1000, AttackAI::Action::invokeAnyoneAttack)},
            {SpawnAsteroids, AI::Pattern(250, AttackAI::Action::spawnAsteroidsAttack)}});

    const std::unordered_map<AttackAI::AIType, AttackAI::AI> AttackAI::_aiVector({{None, AttackAI::AI({WaitLong})},
        {Battlecruiser, AttackAI::AI({ShootLaser, ShootBullet, ShootEnergySphere})},
        {Dreadnought, AttackAI::AI({InvokeAllies})}, {Fighter, AttackAI::AI({ShootLaser, ShootBullet})},
        {Frigate, AttackAI::AI({ShootEnergySphere})}, {Scout, AttackAI::AI({ShootLaser})},
        {Torpedo, AttackAI::AI({ShootRocket})},
        {NoodleMonster,
            AttackAI::AI({SpawnAsteroids, SpawnAsteroids, InvokeAnyone, ShootEnergySphereFast, ShootEnergySphereFast,
                ShootEnergySphereFast, ShootEnergySphereFast, ShootEnergySphereFast, ShootEnergySphereFast})}});
} // namespace ecs::component
