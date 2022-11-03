#include "EntityAI.hpp"

namespace ecs::component
{
    const std::unordered_map<EntityAI::AIType, EntityAI::AI> EntityAI::_aiVector({
        {Idle, EntityAI::AI({{0, 0}}, 100)},
        {BasicUpDown, EntityAI::AI({{0, 1}, {0, -1}}, 2)}
    });
}
