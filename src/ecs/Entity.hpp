#ifndef ECS_ENTITY_
#define ECS_ENTITY_

#include <cstddef>

/**
 * Entity class is represented by a simple entity_t according to the global functioning of the ECS
 */
namespace ecs {
    class Entity {
        public:
            friend class Registry;

            /**
             * Operators for the Entity class used to get the Id of the entity
             * @return Private member _id of the Entity
             */
            explicit operator size_t &() { return _id; }

            explicit operator size_t() const { return _id; }

            static const std::size_t npos = -1;

        private:
            explicit Entity(size_t id) : _id(id) {}

            size_t &operator=(const std::size_t &id) {
                _id = id;
                return _id;
            }

            std::size_t _id;
    };
}

#endif // ECS_ENTITY_