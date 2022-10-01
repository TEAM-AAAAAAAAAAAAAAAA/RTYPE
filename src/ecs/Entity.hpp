#ifndef ECS_ENTITY_
#define ECS_ENTITY_

#include <cstddef>

class Entity
{
public:
    friend class Registry;

    operator std::size_t &() { return _id; }
    operator std::size_t() const { return _id; }

    static const std::size_t npos = -1;

private:
    Entity(std::size_t id) : _id(id) {}
    std::size_t &operator=(const std::size_t &id)
    {
        _id = id;
        return _id;
    }
    std::size_t _id;
};

#endif // ECS_ENTITY_