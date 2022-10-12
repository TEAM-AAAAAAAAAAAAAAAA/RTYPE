/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include <iostream>
#include "Engine.hpp"
#include "components/Direction.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "systems/Movement.hpp"
#include "systems/PositionLogger.hpp"
#ifdef CLIENT_COMPILATION_MODE
    #include "SFML/Graphics.hpp"
    #include "components/Controllable.hpp"
    #include "components/Drawable.hpp"
    #include "components/EnemyAI.hpp"
    #include "systems/Draw.hpp"
    #include "systems/HandleSFMLEvents.hpp"
    #include "systems/HandleSFMLMovements.hpp"
    #include "systems/ManageClientEvents.hpp"
#endif

ecs::World getGameWorld(ecs::Engine &engine)
{
    ecs::World world(engine.getWindow());

    ecs::Entity player = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(player, {10, 10});
    world.registry.addComponent<ecs::component::Velocity>(player, {5, 5});
    world.registry.addComponent<ecs::component::Size>(player, {2, 2});
    world.registry.addComponent<ecs::component::Direction>(player, {1, 0});
    world.addSystem(ecs::systems::positionLogger);
    world.addSystem(ecs::systems::movement);

#ifdef CLIENT_COMPILATION_MODE
    world.registry.addComponent<ecs::component::Controllable>(
        player, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D});
    world.registry.addComponent<ecs::component::Drawable>(
        player, {"src/demo/assets/textures/players.gif", {1, 1, 32, 16}});

    ecs::Entity enemy = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy, {500, 500});
    world.registry.addComponent<ecs::component::Size>(enemy, {5, 5});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy, {});
    world.registry.addComponent<ecs::component::Drawable>(
        enemy, {"src/demo/assets/textures/players.gif", {1, 18, 32, 16}});
    world.addSystem(ecs::systems::handleSFMLEvents);
    world.addSystem(ecs::systems::handleSFMLMovements);

    world.addSystem(ecs::systems::manageClientEvents);
    world.addSystem(ecs::systems::draw);
#endif
    return world;
}

int main()
{
    ecs::Engine engine;
    engine.setWaitingWorld(getGameWorld(engine));

    engine.run();
    return 0;
}
