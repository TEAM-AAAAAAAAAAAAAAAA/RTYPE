/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include <iostream>
#include "../ecs/Engine.hpp"

int main()
{
    ecs::Engine e;

    while (true) {
        e.run();
    }
    // ecs::Registry r;
    // ecs::Entity e = r.spawn_entity();
    // r.emplaceComponent<ecs::component::Position>(e, 1, 2);
    // r.emplaceComponent<ecs::component::Velocity>(e, 1, 1);
    // sf::Clock clock;
    // while (true)
    // {
    //     ecs::systems::movement(r);
    //     ecs::systems::positionLogger(r);
    // }
    return 0;
}
