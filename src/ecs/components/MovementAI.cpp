#include "MovementAI.hpp"

namespace ecs::component
{
    static const std::pair<char, char> STOP = {0, 0};
    static const std::pair<char, char> UP = {0, -1};
    static const std::pair<char, char> UP_LEFT = {-1, -1};
    static const std::pair<char, char> LEFT = {-1, 0};
    static const std::pair<char, char> DOWN_LEFT = {-1, 1};
    static const std::pair<char, char> DOWN = {0, 1};
    static const std::pair<char, char> DOWN_RIGHT = {1, 1};
    static const std::pair<char, char> RIGHT = {1, 0};
    static const std::pair<char, char> UP_RIGHT = {1, -1};

    const std::unordered_map<MovementAI::AIType, MovementAI::AI> MovementAI::_aiVector({
        {Idle, MovementAI::AI({{0, 0}}, 100)},
        {QuickUpDown, MovementAI::AI({UP, DOWN}, 5)},
        {LongUpDown, MovementAI::AI({UP, DOWN}, 15)},
        {QuickLeftRight, MovementAI::AI({LEFT, RIGHT}, 5)},
        {LongLeftRight, MovementAI::AI({LEFT, RIGHT}, 15)},
        {ClockwiseSmall, MovementAI::AI({DOWN_RIGHT, DOWN_LEFT, UP_LEFT, UP_RIGHT}, 5)},
        {ClockwiseBig, MovementAI::AI({DOWN_RIGHT, DOWN_LEFT, UP_LEFT, UP_RIGHT}, 15)},
        {AntiClockwiseSmall, MovementAI::AI({DOWN_LEFT, DOWN_RIGHT, UP_RIGHT, UP_LEFT}, 5)},
        {AntiClockwiseBig, MovementAI::AI({DOWN_LEFT, DOWN_RIGHT, UP_RIGHT, UP_LEFT}, 15)}
    });
}
