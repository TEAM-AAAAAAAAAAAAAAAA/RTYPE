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
        static short maxPlayerHealth = 100;
        static short sizeHealthBar = 282;

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
            ROOM_INFO,
            KEEP_ALIVE,
            HEALTH_UPDATE,
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
            OPTION,
            QUIT,
            PLAY_HOVER,
            OPTION_HOVER,
            QUIT_HOVER,
            ROOM,
            ROOM_HOVER,
            ROOM_TEXT,
            UNDEFINED
        };

        struct ButtonValue {
            short rectLeft;
            short rectTop;
            short defaultRectWidth;
            short defaultRectHeight;
            short rectWidth;
            short rectHeight;
            short posX;
            short posY;
        };

        static const std::map<ButtonType, ButtonValue> buttonValueMap {
            {PLAY, {324, 2079, 916, 292, 200, 63, 100, 250}},
            {OPTION, {3651, 2079, 916, 292, 200, 63, 100, 420}},
            {QUIT, {4760, 2079, 916, 292, 200, 63, 100, 590}},
            {PLAY_HOVER, {220, 2449, 1114, 356, 200, 63, 100, 250}},
            {OPTION_HOVER, {3542, 2456, 1114, 356, 200, 63, 100, 420}},
            {QUIT_HOVER, {4670, 2451, 1114, 356, 200, 63, 100, 590}},
            {ROOM, {326, 456, 1114, 356, 400, 63, 600, 250}},
            {ROOM_HOVER, {326, 1510, 1114, 356, 400, 63, 600, 250}},
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
            {70, KEEP_ALIVE},
            {128, ROOM_INFO},
            {38, HEALTH_UPDATE}
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
