#include <iostream>
#include "SparseArray.hpp"
#include "ecs.hpp"

void demo(void)
{
    int c = 4;
    size_t i = 5;

    SparseArray<int> a;

    a.insert_at(i, c);

    std::cout << a[i].has_value() << std::endl;

    SparseArray<int> b(a);

    std::cout << b[i].has_value() << std::endl;
}
