#include "EnemyAI.hpp"

namespace ecs::component
{
    const std::unordered_map<EnemyAI::AIType, EnemyAI::AI> EnemyAI::_aiVector({
        {Idle, EnemyAI::AI({{0, 0}}, 100)},
        {BasicUpDown, EnemyAI::AI({{1, 0}, {-1, 0}}, 2)}
    });
}
