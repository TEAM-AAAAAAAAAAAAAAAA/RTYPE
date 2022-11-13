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
            WAVE_UPDATE,
            ROOM_UPDATE,
            HUB_CONNECT,
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
            OPTION_INTERFACE,
            SOUND_LEFT,
            SOUND_RIGHT,
            SOUND_LEFT_HOVER,
            SOUND_RIGHT_HOVER,
            MUSIC_LEFT,
            MUSIC_RIGHT,
            MUSIC_RIGHT_HOVER,
            MUSIC_LEFT_HOVER,
            HOW_TO,
            HOW_TO_HOVER,
            SLIDE_MUSIC,
            SLIDE_SOUND,
            SOUND_BAR,
            SETTINGS,
            SETTINGS_HOVER,
            OPTIONS_TEXT,
            PLANET,
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
            {PLAY, {337, 2073, 916, 292, 300, 100, 300, 280}},
            {OPTION, {3664, 2073, 916, 292, 300, 100, 300, 480}},
            {QUIT, {4773, 2073, 916, 292, 300, 100, 300, 680}},
            {PLAY_HOVER, {220, 2449, 1114, 356, 300, 100, 300, 280}},
            {OPTION_HOVER, {3542, 2456, 1114, 356, 300, 100, 300, 450}},
            {QUIT_HOVER, {4670, 2451, 1114, 356, 300, 100, 300, 620}},
            {ROOM, {326, 456, 1114, 356, 400, 100, 850, 250}},
            {OPTION_INTERFACE, {1692, 168, 1589, 1790, 692, 772, 800, 100}},
            {SOUND_LEFT, {3813, 178, 255, 256, 55, 55, 1260, 560}},
            {SOUND_RIGHT, {3489, 434, 255, 256, 55, 55, 1325, 560}},
            {SOUND_LEFT_HOVER, {3489, 178, 255, 256, 55, 55, 1260, 560}},
            {SOUND_RIGHT_HOVER, {3813, 434, 255, 256, 55, 55, 1325, 560}},
            {MUSIC_LEFT, {3813, 178, 255, 256, 55, 55, 1260, 360}},
            {MUSIC_RIGHT, {3489, 434, 255, 256, 55, 55, 1325, 360}},
            {MUSIC_LEFT_HOVER, {3489, 178, 255, 256, 55, 55, 1260, 360}},
            {MUSIC_RIGHT_HOVER, {3813, 434, 255, 256, 55, 55, 1325, 360}},
            {HOW_TO, {4137, 434, 255, 256, 55, 55, 1250, 700}},
            {HOW_TO_HOVER, {4137, 178, 255, 256, 55, 55, 1250, 700}},
            {SLIDE_SOUND, {4396, 1486, 97, 146, 21, 31, 1070, 572}},
            {SLIDE_MUSIC, {4396, 1486, 97, 146, 21, 31, 1070, 372}},
            {SOUND_BAR, {3476, 1692, 2213, 168, 350, 36, 900, 370}},
            {SETTINGS, {4461, 435, 255, 255, 55, 55, 970, 700}},
            {SETTINGS_HOVER, {4461, 178, 255, 255, 55, 55, 970, 700}},

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
            {3, NEW_WAVE},
            {7, BOSS_STAGE},
            {15, GAME_OVER},
            {31, MULTIPLAYER_INFO},
            {38, HEALTH_UPDATE},
            {40, WAVE_UPDATE},
            {70, KEEP_ALIVE},
            {127, ROOM_INFO},
            {61, ROOM_UPDATE}
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
