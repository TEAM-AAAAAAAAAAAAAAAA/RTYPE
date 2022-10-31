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
        /**
         * @brief AnimFrame struct
         *
         * @param x pos of the top left corner of the frame
         * @param y pos of the top left corner of the frame
         * @param width of the frame
         * @param height of the frame
         * @param delay before the next frame
         */
        struct AnimFrame {
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
        Animated(const AnimFrame &frame) { _loadFrames(frame); }

        /**
         * @brief Construct a new Animated object
         *
         * @param first
         * @param frames
         */
        Animated(const AnimFrame &first, AnimFrame frames...) { _loadFrames(first, frames); }

        int64_t lastSwitch;

        AnimFrame getFrame() { return _animFrames[_currentFrame]; }

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
            if (_currentFrame < _animFrames.size())
                _currentFrame++;
            else
                _currentFrame = 0;
        }

      private:
        void _loadFrames(AnimFrame first) { _animFrames.push_back(first); }
        void _loadFrames(AnimFrame first, AnimFrame frames...)
        {
            _animFrames.push_back(first);
            _loadFrames(frames);
        }

        int _currentFrame;
        std::vector<AnimFrame> _animFrames;
    };
} // namespace ecs::component
