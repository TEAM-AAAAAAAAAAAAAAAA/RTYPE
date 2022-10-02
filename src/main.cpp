#include <iostream>
#include "ecs/Registry.hpp"
#include "ecs/components/Position.hpp"

int main()
{
    ecs::Registry r;
    ecs::SparseArray<ecs::Position> p;
    std::cout << "Hello World!" << std::endl;
    return 0;
}