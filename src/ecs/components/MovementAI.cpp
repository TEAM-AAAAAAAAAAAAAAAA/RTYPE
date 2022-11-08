#include "MovementAI.hpp"

namespace ecs::component
{
    const std::unordered_map<MovementAI::AIType, MovementAI::AI> MovementAI::_aiVector({
        {Idle, MovementAI::AI({{0, 0}}, 100)},
        {BasicUpDown, MovementAI::AI({{0, 1}, {0, -1}}, 2)}
    });
}
