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
#include "systems/ShowHitBox.hpp"

ecs::World getGameWorld(ecs::Engine &engine)
{
    ecs::World world(engine.getWindow());

    ecs::Entity player = world.registry.spawn_entity();
    const std::filesystem::path &playerPath = ecs::crossPlatformPath("src", "demo", "assets", "textures", "players.gif");
    world.registry.registerComponent<ecs::component::Projectile>();

    world.registry.addComponent<ecs::component::Position>(player, {10, 10});
    world.registry.addComponent<ecs::component::Velocity>(player, {5, 5});
    world.registry.addComponent<ecs::component::Size>(player, {32, 64});
    world.registry.addComponent<ecs::component::Direction>(player, {1, 0});
    world.registry.addComponent<ecs::component::Weapon>(player, {100, 10, 10});
    world.registry.addComponent<ecs::component::Health>(player, {2000});
    world.registry.addComponent<ecs::component::Faction>(player, {ecs::component::Faction::Factions::Players});
    // world.addSystem(ecs::systems::positionLogger);
    world.addSystem(ecs::systems::movement);
    world.addSystem(ecs::systems::projectileCollision);
    world.addSystem(ecs::systems::ShowHitBox);

    ecs::Entity enemy = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy, {500, 50});
    world.registry.addComponent<ecs::component::Size>(enemy, {64, 128});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy, {});
    world.registry.addComponent<ecs::component::Health>(enemy, {100});
    world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Enemies});
    world.registry.addComponent<ecs::component::Drawable>(enemy, {playerPath, {1, 18, 32, 16}});
// TO DELETE ---------------------------------------------------------------------------------------------------------------------------------------
    ecs::Entity enemy_1 = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy_1, {500, 100});
    world.registry.addComponent<ecs::component::Size>(enemy_1, {64, 128});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy_1, {});
    world.registry.addComponent<ecs::component::Health>(enemy_1, {100});
    world.registry.addComponent<ecs::component::Faction>(enemy_1, {ecs::component::Faction::Factions::Enemies});
    world.registry.addComponent<ecs::component::Drawable>(enemy_1, {playerPath, {1, 18, 32, 16}});


    ecs::Entity enemy_2 = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy_2, {500, 200});
    world.registry.addComponent<ecs::component::Size>(enemy_2, {64, 128});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy_2, {});
    world.registry.addComponent<ecs::component::Health>(enemy_2, {110});
    world.registry.addComponent<ecs::component::Faction>(enemy_2, {ecs::component::Faction::Factions::Enemies});
    world.registry.addComponent<ecs::component::Drawable>(enemy_2, {playerPath, {1, 18, 32, 16}});

    ecs::Entity enemy_3 = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy_3, {500, 300});
    world.registry.addComponent<ecs::component::Size>(enemy_3, {64, 128});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy_3, {});
    world.registry.addComponent<ecs::component::Health>(enemy_3, {120});
    world.registry.addComponent<ecs::component::Faction>(enemy_3, {ecs::component::Faction::Factions::Enemies});
    world.registry.addComponent<ecs::component::Drawable>(enemy_3, {playerPath, {1, 18, 32, 16}});

    ecs::Entity enemy_4 = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy_4, {500, 400});
    world.registry.addComponent<ecs::component::Size>(enemy_4, {64, 128});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy_4, {});
    world.registry.addComponent<ecs::component::Health>(enemy_4, {130});
    world.registry.addComponent<ecs::component::Faction>(enemy_4, {ecs::component::Faction::Factions::Enemies});
    world.registry.addComponent<ecs::component::Drawable>(enemy_4, {playerPath, {1, 18, 32, 16}});

    ecs::Entity enemy_5 = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy_5, {500, 500});
    world.registry.addComponent<ecs::component::Size>(enemy_5, {64, 128});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy_5, {});
    world.registry.addComponent<ecs::component::Health>(enemy_5, {140});
    world.registry.addComponent<ecs::component::Faction>(enemy_5, {ecs::component::Faction::Factions::Enemies});
    world.registry.addComponent<ecs::component::Drawable>(enemy_5, {playerPath, {1, 18, 32, 16}});
// TO DELETE ---------------------------------------------------------------------------------------------------------------------------------------
    world.registry.addComponent<ecs::component::Controllable>(
        player, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D});
    world.registry.addComponent<ecs::component::Drawable>(player, {playerPath, sf::IntRect(1, 1, 32, 16)});
    world.registry.addComponent<ecs::component::Shootable>(player, ecs::component::Shootable(sf::Keyboard::Space));

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
