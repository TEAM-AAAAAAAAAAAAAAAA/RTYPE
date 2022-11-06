#include "AttackAI.hpp"

namespace ecs::component
{
    void shootBulletAttack(World &world, const std::size_t &shooter) { std::cout << "shoot bullet" << std::endl; }

    void shootEneryBallsAttack(World &world, const std::size_t &shooter)
    {
        std::cout << "shoot energy ball" << std::endl;
    }

    const std::unordered_map<AttackAI::PatternType, AttackAI::AI::Pattern> AttackAI::AI::_patternMap(
        {{ShootBullet, {2, shootBulletAttack}}, {ShootEnergyBalls, {3, shootEneryBallsAttack}}});

    const std::unordered_map<AttackAI::AIType, AttackAI::AI> AttackAI::_aiVector(
        {{Scout, AttackAI::AI({ShootBullet})}, {Fighter, AttackAI::AI({ShootBullet, ShootEnergyBalls})}});
} // namespace ecs::component
