#ifndef ECS_ENTITY_
#define ECS_ENTITY_

#include <cstddef>

class Entity
{
public:
    friend class Registry;

    operator size_t &() { return _id; }
    operator size_t() const { return _id; }

private:
    Entity(size_t id) : _id(id) {}
    size_t &operator=(const size_t &id)
    {
        _id = id;
        return _id;
    }
    size_t _id;
};

#endif // ECS_ENTITY_