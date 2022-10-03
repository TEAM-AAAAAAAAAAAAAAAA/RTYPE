/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include "../ecs/Registry.hpp"
#include "../ecs/components/Position.hpp"
#include "../ecs/components/Velocity.hpp"
#include "../ecs/systems/Movement.hpp"
#include "../ecs/systems/PositionLogger.hpp"
#include <iostream>

int main()
{
    ecs::Registry r;
    ecs::Entity e = r.spawn_entity();
    r.emplaceComponent<ecs::component::Position>(e, 1, 2);
    r.emplaceComponent<ecs::component::Velocity>(e, 1, 2);
    while (true)
    {
        ecs::systems::movement(r);
        ecs::systems::positionLogger(r);
    }
    return 0;
}