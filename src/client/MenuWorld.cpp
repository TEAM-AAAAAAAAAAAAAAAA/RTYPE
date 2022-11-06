/*
** EPITECH PROJECT, by hourcadettej on 11/6/22.
** rtype
** File description:
** rtype
*/

#include "MenuWorld.hpp"

#include "components/Direction.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/client/Animated.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Drawable.hpp"

#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/client/Draw.hpp"
#include "systems/client/HandleSFMLEvents.hpp"
#include "systems/client/HandleSFMLKeys.hpp"

static const int FRAME_LIMIT = 60;

static void registerAllComponent(ecs::World &world)
{
    world.registry.registerComponent<ecs::component::Controllable>();
    world.registry.registerComponent<ecs::component::Weapon>();
    world.registry.registerComponent<ecs::component::Size>();
    world.registry.registerComponent<ecs::component::Position>();
    world.registry.registerComponent<ecs::component::Projectile>();
    world.registry.registerComponent<ecs::component::Direction>();
    world.registry.registerComponent<ecs::component::Drawable>();
    world.registry.registerComponent<ecs::component::Shootable>();
    world.registry.registerComponent<ecs::component::Animated>();
}

static void addAllSystems(ecs::World &world)
{
    world.addSystem(ecs::systems::handleSFMLEvents);
    world.addSystem(ecs::systems::handleSFMLKeys);
    world.addSystem(ecs::systems::manageClientEvents);
    world.addSystem(ecs::systems::draw);
    world.addSystem(ecs::systems::movement);
}

static void setBackground(ecs::World &world)
{
    //TODO Need to implement the background of the menu, assets, button etc...
}

ecs::World getMenuWorld()
{
    ecs::World world;

    utils::Window::get().setFramerateLimit(FRAME_LIMIT);
    registerAllComponent(world);
    addAllSystems(world);
    setBackground(world);
    return world;
}