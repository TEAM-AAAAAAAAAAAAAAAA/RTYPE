/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include <iostream>
#include "../ecs/Registry.hpp"
#include "../ecs/components/Position.hpp"

int main()
{
    ecs::Registry r;

    ecs::Entity player = r.spawn_entity();
    ecs::Entity enemy = r.spawn_entity();
    r.registerComponent<ecs::component::Position>();
    r.addComponent(player, ecs::component::Position{10, 10});
    r.addComponent(enemy, ecs::component::Position{200, 200});


    return 0;
}