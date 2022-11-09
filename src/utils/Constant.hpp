/*
** EPITECH PROJECT, by hourcadettej on 10/2/22.
** rtype
** File description:
** rtype
*/

#pragma once

#include <chrono>
#include <cstddef>
#include <map>
#include <algorithm>

namespace utils
{
    namespace constant
    {
        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;

        static const std::size_t npos = -1;
        static short mapWidth = 1920;
        static short mapHeight = 1080;

        enum PacketType {
            PLAYER_MOVE = 8,
            PLAYER_SHOT = 2,
            PLAYER_CHARGED_SHOT,
            PLAYER_POWERUP,
            ENTITY_MOVE,
            ENTITY_SPAWN,
            ENTITY_DEATH,
            ENTITY_DAMAGE,
            ENTITY_HEAL,
            NEW_WAVE,
            BOSS_STAGE,
            GAME_OVER,
            MULTIPLAYER_INFO,
            NONE
        };

        enum ButtonActionType {
            PLAY_ACTION,
            QUIT_ACTION,
            OPTIONS_ACTION,
            CONNECT_ACTION
        };

        enum ButtonType {
            PLAY,
            OPTIONS,
            QUIT,
            PLAY_HOVER,
            OPTION_HOVER,
            QUIT_HOVER,
        };

        struct ButtonValue {
            short rectLeft;
            short rectTop;
            short defaultRectWidth;
            short defaultRectHeight;
            short rectWidth;
        };

        static const std::map<ButtonType, ButtonValue> buttonValueMap {
            {PLAY, {324, 2079, 916, 292, 200}},
            {OPTIONS, {3651, 2079, 916, 292, 200}},
            {QUIT, {4760, 2079, 916, 292, 200}},
            {PLAY_HOVER, {220, 2449, 1114, 356, 200}},
            {OPTION_HOVER, {3542, 2456, 1114, 356, 200}},
            {QUIT_HOVER, {4670, 2451, 1114, 356, 200}},
        };

        static std::map<int, PacketType> mapPacketType{
            {1, PLAYER_MOVE},
            {2, PLAYER_SHOT},
            {4, PLAYER_CHARGED_SHOT},
            {8, ENTITY_MOVE},
            {16, ENTITY_SPAWN},
            {17, ENTITY_DEATH},
            {32, ENTITY_DAMAGE},
            {34, ENTITY_HEAL},
            {64, PLAYER_POWERUP},
            {3, NEW_WAVE},
            {7, BOSS_STAGE},
            {15, GAME_OVER},
            {31, MULTIPLAYER_INFO},
        };

        static int getPacketTypeKey(PacketType type)
        {
            auto result = std::find_if(
                mapPacketType.begin(), mapPacketType.end(), [type](const auto &mo) { return mo.second == type; });
            if (result != mapPacketType.end()) {
                int foundkey = result->first;
                return foundkey;
            }
            return -1;
        }
    } // namespace constant
} // namespace utils
