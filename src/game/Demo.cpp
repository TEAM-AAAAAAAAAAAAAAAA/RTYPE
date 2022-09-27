#include <iostream>
#include "ecs/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "components/Position.hpp"

void demo(void)
{
    Registry r;

    r.register_component<Position>();

    Entity e = r.spawn_entity();
    Entity f = r.spawn_entity();
    auto test = r.add_component<Position>(e, {1, 2});
    auto test2 = r.add_component<Position>(f, {1, 2});
    (void)test;
    (void)test2;
    r.remove_component<Position>(e);
    // r.kill_entity(e);
    // r.add_component<Position>(e, {1, 2});

    auto positions = r.get_components<Position>();
    (void)positions;
}
