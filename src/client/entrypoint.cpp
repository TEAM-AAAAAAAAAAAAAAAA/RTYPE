/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include <iostream>
#include "Engine.hpp"
#include "SFML/Graphics.hpp"
#include "components/Controllable.hpp"
#include "components/Direction.hpp"
#include "components/Drawable.hpp"
#include "components/EnemyAI.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/Weapon.hpp"
#include "systems/Draw.hpp"
#include "systems/HandleSFMLEvents.hpp"
#include "systems/HandleSFMLKeys.hpp"
#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/PositionLogger.hpp"
#include "systems/ProjectileCollision.hpp"

ecs::World getGameWorld(ecs::Engine &engine)
{
    ecs::World world(engine.getWindow());

    ecs::Entity player = world.registry.spawn_entity();

    world.registry.registerComponent<ecs::component::Projectile>();

    world.registry.addComponent<ecs::component::Position>(player, {10, 10});
    world.registry.addComponent<ecs::component::Velocity>(player, {5, 5});
    world.registry.addComponent<ecs::component::Size>(player, {32, 64});
    world.registry.addComponent<ecs::component::Direction>(player, {1, 0});
    world.registry.addComponent<ecs::component::Weapon>(player, {100, 10, 10});
    world.registry.addComponent<ecs::component::Health>(player, {100});
    world.registry.addComponent<ecs::component::Faction>(player, {ecs::component::Faction::Factions::Players});
    // world.addSystem(ecs::systems::positionLogger);
    world.addSystem(ecs::systems::movement);
    world.addSystem(ecs::systems::projectileCollision);

    ecs::Entity enemy = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy, {500, 500});
    world.registry.addComponent<ecs::component::Size>(enemy, {64, 128});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy, {});
    world.registry.addComponent<ecs::component::Health>(enemy, {100});
    world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Enemies});

    const std::filesystem::path &playerPath = ecs::crossPlatformPath("src", "demo", "assets", "textures", "players.gif");
    world.registry.addComponent<ecs::component::Controllable>(
        player, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D});
    world.registry.addComponent<ecs::component::Drawable>(player, {playerPath, sf::IntRect(1, 1, 32, 16)});
    world.registry.addComponent<ecs::component::Shootable>(player, ecs::component::Shootable(sf::Keyboard::Space));
    world.registry.addComponent<ecs::component::Drawable>(enemy, {playerPath, {1, 18, 32, 16}});

    world.addSystem(ecs::systems::handleSFMLEvents);
    world.addSystem(ecs::systems::handleSFMLKeys);
    world.addSystem(ecs::systems::manageClientEvents);
    world.addSystem(ecs::systems::draw);
    return world;
}

int main()
{
    ecs::Engine engine;
    engine.setWaitingWorld(getGameWorld(engine));

    engine.run();
    return 0;
}
