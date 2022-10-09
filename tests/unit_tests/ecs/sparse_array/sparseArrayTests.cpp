/*
** EPITECH PROJECT, by hourcadettej on 9/29/22.
** rtype
** File description:
** rtype
*/

#include <criterion/criterion.h>
#include "SparseArray.hpp"
#include "components/Position.hpp"

Test(basic_sparse_test, reference_test)
{
    cr_assert_eq(1, 1);
}

//Test(operator_sparse_array, copy)
//{
//    ecs::component::Position p1{1, 1};
//    ecs::component::Position p2{2, 2};
//    ecs::SparseArray<ecs::component::Position> sA1;
//    ecs::SparseArray<ecs::component::Position> sA2;
//
//    sA1.insertAt(0, p1);
//    sA1.insertAt(1, p2);
//    sA2.operator=(sA1);
//    cr_assert_eq(sA2.begin()->value().x, 1)
//    cr_assert_eq(sA2.begin()->value().y, 1)
//}

//Test(operator_sparse_array, moove)
//{
//    ecs::component::Position p1{1, 1};
//    ecs::component::Position p2{2, 2};
//    ecs::SparseArray<ecs::component::Position> sA1;
//    ecs::SparseArray<ecs::component::Position> sA2;
//
//    sA1.insertAt(0, p1);
//    sA1.insertAt(1, p2);
//    sA1.operator=(sA2);
//}

Test(begin, basic_test)
{
    ecs::component::Position p1{1, 1};
    ecs::component::Position p2{2, 2};
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.insertAt(0, p1);
    sA1.insertAt(1, p2);
    cr_assert_eq(sA1.begin()->value().x, 1);
    cr_assert_eq(sA1.begin()->value().y, 1);
}

Test(end, basic_test)
{
    ecs::component::Position p1{1, 1};
    ecs::component::Position p2{2, 2};
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.insertAt(0, p1);
    sA1.insertAt(1, p2);
    cr_assert_eq(sA1.end()->value().x, 2);
    cr_assert_eq(sA1.end()->value().y, 2);
}

Test(size, size_of_zero)
{
    ecs::SparseArray<ecs::component::Position> sA1;

    cr_assert_eq(sA1.size(), 0);
}

Test(size, size_of_two)
{
    ecs::component::Position p1{1, 1};
    ecs::component::Position p2{2, 2};
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.insertAt(0, p1);
    sA1.insertAt(1, p2);
    cr_assert_eq(sA1.size(), 2);
}

Test(size, size_of_ten)
{
    ecs::component::Position p1{1, 1};
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.insertAt(0, p1);
    sA1.insertAt(1, p1);
    sA1.insertAt(2, p1);
    sA1.insertAt(3, p1);
    sA1.insertAt(4, p1);
    sA1.insertAt(5, p1);
    sA1.insertAt(6, p1);
    sA1.insertAt(7, p1);
    sA1.insertAt(8, p1);
    sA1.insertAt(9, p1);
    cr_assert_eq(sA1.size(), 10);
}

Test(insertAt, different_pos)
{
    ecs::component::Position p1{1, 1};
    ecs::component::Position p2{2, 2};
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.insertAt(0, p1);
    sA1.insertAt(1, p2);
    cr_assert_eq(sA1.size(), 2);
    cr_assert_eq(sA1.begin()->value().y, 1);
    cr_assert_eq(sA1.begin()->value().x, 1);
    cr_assert_eq(sA1.end()->value().x, 2);
    cr_assert_eq(sA1.end()->value().y, 2);
}

Test(insertAt, same_pos)
{
    ecs::component::Position p1{1, 1};
    ecs::component::Position p2{2, 2};
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.insertAt(0, p1);
    sA1.insertAt(0, p2);
    cr_assert_eq(sA1.size(), 2);
    cr_assert_eq(sA1.begin()->value().y, 2);
    cr_assert_eq(sA1.begin()->value().x, 2);
    cr_assert_eq(sA1.end()->value().x, 1);
    cr_assert_eq(sA1.end()->value().y, 1);
}

Test(emplaceAt, same_pos)
{
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.emplaceAt(0, ecs::component::Position{1, 1});
    sA1.emplaceAt(0, ecs::component::Position{2, 2});
    cr_assert_eq(sA1.size(), 2);
    cr_assert_eq(sA1.begin()->value().y, 2);
    cr_assert_eq(sA1.begin()->value().x, 2);
    cr_assert_eq(sA1.end()->value().x, 1);
    cr_assert_eq(sA1.end()->value().y, 1);
}

Test(emplaceAt, different_pos)
{
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.emplaceAt(0, ecs::component::Position{1, 1});
    sA1.emplaceAt(1, ecs::component::Position{2, 2});
    cr_assert_eq(sA1.size(), 2);
    cr_assert_eq(sA1.begin()->value().y, 1);
    cr_assert_eq(sA1.begin()->value().x, 1);
    cr_assert_eq(sA1.end()->value().x, 2);
    cr_assert_eq(sA1.end()->value().y, 2);
}

Test(erase, basic_test)
{
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.emplaceAt(0, ecs::component::Position{1, 1});
    sA1.emplaceAt(1, ecs::component::Position{2, 2});
    cr_assert_eq(sA1.size(), 2);
    sA1.erase(1);
    cr_assert_eq(sA1.size(), 2);
    cr_assert_eq(sA1.begin()->value().y, 1);
    cr_assert_eq(sA1.begin()->value().x, 1);
}

Test(erase, erase_them_all)
{
    ecs::SparseArray<ecs::component::Position> sA1;

    sA1.emplaceAt(0, ecs::component::Position{1, 1});
    sA1.emplaceAt(1, ecs::component::Position{2, 2});
    cr_assert_eq(sA1.size(), 2);
    sA1.erase(0);
    sA1.erase(1);
    cr_assert_eq(sA1.size(), 2);
    cr_assert_eq(sA1.begin()->has_value(), false);
}

//Test(getIndex, basic_test)
//{
//    ecs::component::Position p1{1, 1};
//    ecs::component::Position p2{2, 2};
//    ecs::SparseArray<ecs::component::Position> sA1;
//
//    sA1.insertAt(0, p1);
//    sA1.insertAt(0, p2);
//    cr_assert_eq(sA1.getIndex(std::nullopt), 1);
//}
