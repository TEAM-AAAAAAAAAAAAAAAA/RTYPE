/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Animated
*/

#pragma once

#include <vector>

namespace ecs::component
{
    struct Animated {
        struct AnimFrame {
            /**
             * @brief AnimFrame struct
             *
             * @param x pos of the top left corner of the frame
             * @param y pos of the top left corner of the frame
             * @param width of the frame
             * @param height of the frame
             * @param delay before the next frame
             */
            AnimFrame(int x, int y, int width, int height, int delay)
                : x(x), y(y), width(width), height(height), delay(delay)
            {
            }
            int x;
            int y;
            int width;
            int height;
            int delay;
        };

        /**
         * @brief Construct a new Animated object with only one frame (replace Drawable's rect)
         *
         * @param first the only frame of the spritesheet
         */
        Animated(const AnimFrame &frame) : _currentFrame(0), lastSwitch(0) { _loadFrames(frame); }

        /**
         * @brief Construct a new Animated object
         *
         * @param first
         * @param frames
         */
        template <class... Frames> Animated(const AnimFrame &first, Frames... frames) : _currentFrame(0), lastSwitch(0)
        {
            _loadFrames(first, frames...);
        }

        int64_t lastSwitch;

        AnimFrame getFrame()
        {
            return _animFrames[_currentFrame];
        }

        const AnimFrame getFrame() const { return _animFrames[_currentFrame]; }

        sf::IntRect getFrameRect()
        {
            return sf::IntRect(_animFrames[_currentFrame].x, _animFrames[_currentFrame].y,
                _animFrames[_currentFrame].width, _animFrames[_currentFrame].height);
        }

        const sf::IntRect getFrameRect() const
        {
            return sf::IntRect(_animFrames[_currentFrame].x, _animFrames[_currentFrame].y,
                _animFrames[_currentFrame].width, _animFrames[_currentFrame].height);
        }

        void nextFrame()
        {
            if (_currentFrame < _animFrames.size() - 1)
                _currentFrame++;
            else
                _currentFrame = 0;
        }

      private:
        void _loadFrames() {}
        void _loadFrames(AnimFrame first)
        {
            _animFrames.push_back(first);
        }
        template <class... Frames> void _loadFrames(AnimFrame first, Frames... next)
        {
            _animFrames.push_back(first);
            _loadFrames(next...);
        }

        int _currentFrame;
        std::vector<AnimFrame> _animFrames;
    };
} // namespace ecs::component
