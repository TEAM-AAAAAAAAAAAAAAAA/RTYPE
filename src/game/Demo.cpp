#include <iostream>
#include "ecs/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "components/Position.hpp"

void demo(void)
{
    int c = 4;
    size_t i = 5;

    SparseArray<int> a;

    a.insert_at(i, c);

    std::cout << a[i].has_value() << std::endl;

    SparseArray<int> b(a);

    std::cout << b[i].has_value() << std::endl;

    // std::cout << b.get_index(c) << std::endl;

    Registry r;

    r.register_component<Position>();

    auto positions = r.get_components<Position>();
    (void)positions;
}
