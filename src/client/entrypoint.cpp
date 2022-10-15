/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include <iostream>
#include "Engine.hpp"
#include "NetworkClient.hpp"
#include "SFML/Graphics.hpp"
#include "components/Direction.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/Weapon.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Drawable.hpp"
#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/PositionLogger.hpp"
#include "systems/client/Draw.hpp"
#include "systems/client/HandleIncomingMessages.hpp"
#include "systems/client/HandleSFMLEvents.hpp"
#include "systems/client/HandleSFMLKeys.hpp"

ecs::World getGameWorld(ecs::Engine &engine)
{
    ecs::World world(engine.getWindow());

    // ecs::Entity player = world.registry.spawn_entity();

    world.registry.registerComponent<ecs::component::Projectile>();
    world.registry.registerComponent<ecs::component::Velocity>();
    world.registry.registerComponent<ecs::component::Size>();
    world.registry.registerComponent<ecs::component::Direction>();
    world.registry.registerComponent<ecs::component::Weapon>();
    world.registry.registerComponent<ecs::component::Health>();
    world.registry.registerComponent<ecs::component::Faction>();
    world.registry.registerComponent<ecs::component::Drawable>();
    world.registry.registerComponent<ecs::component::Shootable>();
    world.registry.registerComponent<ecs::component::Controllable>();
    world.registry.registerComponent<ecs::component::Position>();

    // world.registry.addComponent<ecs::component::Position>(player, {10, 10});
    // world.registry.addComponent<ecs::component::Velocity>(player, {5, 5});
    // world.registry.addComponent<ecs::component::Size>(player, {32, 64});
    // world.registry.addComponent<ecs::component::Direction>(player, {1, 0});
    // world.registry.addComponent<ecs::component::Weapon>(player, {100, 10, 10});
    // world.registry.addComponent<ecs::component::Health>(player, {100});
    // world.registry.addComponent<ecs::component::Faction>(player, {ecs::component::Faction::Factions::Players});
    // // world.addSystem(ecs::systems::positionLogger);
    // world.addSystem(ecs::systems::movement);

    // ecs::Entity enemy = world.registry.spawn_entity();
    // world.registry.addComponent<ecs::component::Position>(enemy, {500, 500});
    // world.registry.addComponent<ecs::component::Size>(enemy, {64, 128});
    // world.registry.addComponent<ecs::component::Health>(enemy, {100});
    // world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Enemies});

    // const std::filesystem::path &playerPath = ecs::crossPlatformPath("src", "demo", "assets", "textures",
    // "players.gif"); world.registry.addComponent<ecs::component::Controllable>(
    //     player, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D});
    // world.registry.addComponent<ecs::component::Drawable>(player, {playerPath, sf::IntRect(1, 1, 32, 16)});
    // world.registry.addComponent<ecs::component::Shootable>(player, ecs::component::Shootable(sf::Keyboard::Space));
    // world.registry.addComponent<ecs::component::Drawable>(enemy, {playerPath, {1, 18, 32, 16}});

    world.addSystem(ecs::systems::handleSFMLEvents);
    world.addSystem(ecs::systems::handleSFMLKeys);
    world.addSystem(ecs::systems::manageClientEvents);
    world.addSystem(ecs::systems::draw);
    world.addSystem(ecs::systems::HandleIncomingMessages);
    return world;
}

int main()
{
    network::Client::setHost("localhost");
    network::Client::setPort("8000");
    network::Client::connect();
    ecs::Engine engine;
    network::Message msg;
    msg.fill(0);

    engine.setWaitingWorld(getGameWorld(engine));
    network::Client::getOutgoingMessages().push(msg);

    engine.run();
    return 0;
}
