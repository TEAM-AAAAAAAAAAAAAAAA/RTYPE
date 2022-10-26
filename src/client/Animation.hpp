/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>

namespace gui {
    /// \brief Animation class should be used to create an animation in sfml.
    /// \note It contains a vector of texture that will be updated, depending on a duration time, with the function update.
    /// You should define a duration between each frame.
    /// You should define a position for the animation.
    /// You should define a size for the animation.
    /// You should add a texture for the animation.
    /// \warning A texture is always add at the end of the vector of texture.
    class Animation {
        public:
            /// \brief Create a new instance of Animation.
            Animation();

            /// \brief Destroy the instance of Animation. It's set to default.
            ~Animation() = default;

            /// \brief It updates the texture used depending on the duration time and the previous index in the vector of texture.
            void update();

            /// \brief It adds a texture on the vector of texture used for the animation.
            /// \warning Be carful, the texture is added at the end of the vector. Please add texture in the correct order.
            /// \param texturePath The path to load the texture from.
            /// \param position The position from which the texture of the loaded image is to be obtained.
            /// \param size The size to get the texture from in the image loaded.
            /// \throw AnimationException will be thrown if the image cannot be loaded.
            void addTexture(const std::string &texturePath, const sf::Vector2f &position, const sf::Vector2f &size);

            /// \brief It adds a texture on the vector of texture used for the animation.
            /// \warning Be carful, the texture is added at the end of the vector. Please add texture in the correct order.
            /// \param image The image used to create the texture from.
            /// \param position The position from which the texture of the loaded image is to be obtained.
            /// \param size The size to get the texture from in the image loaded.
            /// \throw AnimationException will be thrown if the texture cannot be created.
            void addTexture(const sf::Image &image, const sf::Vector2f &position, const sf::Vector2f &size);

            /// \brief It returns the shape of the animation with the correct texture.
            /// \note Use this function to get the shape to be drawn.
            /// \warning Keep in mind that you need to update the texture with the `update` function.
            /// \return const sf::RectangleShape reference of the shape.
            const sf::RectangleShape &getShape() const;

            /// \brief It move the shape of the animation with the vector2f move.
            /// \note Use this function to move the shape.
            /// \warning Keep in mind that you need to draw the shape again.
            void moveShape(const sf::Vector2f &move);

            /// \brief It sets the duration between each frame of the animation.
            /// \note The animation must be set as millisecond.
            /// \param duration The duration between each frame of the animation as millisecond.
            void setDuration(const std::size_t &duration);

            /// \brief It gets the duration between each frame of the animation.
            /// \return const std::size_t reference of the duration.
            const std::size_t &getDuration() const;

            /// \brief It sets the position of the shape used for the animation.
            /// \param position The position to be set on the shape.
            void setPosition(const sf::Vector2f &position);

            /// \brief It gets the position of the shape used for the animation.
            /// \return const sf::Vector2f reference of the position.
            const sf::Vector2f &getPosition() const;

            /// \brief It sets the size of the shape used for the animation.
            /// \param size The size to be set on the shape.
            void setSize(const sf::Vector2f &size);

            /// \brief It gets the size of the shape used for the animation.
            /// \return const sf::Vector2f reference of the size.
            const sf::Vector2f &getSize() const;

            /// \brief It gets the size of the shape used for the animation.
            /// \return const sf::Vector2f reference of the size.
            const sf::FloatRect getGlobalBounds();

            /// \brief It sets the color of the shape used for the animation.
            /// \param color The color to be set on the shape.
            void setColor(const sf::Color &color);

            /// \brief It gets the color of the shape used for the animation.
            /// \return const sf::Color reference of the size.
            const sf::Color &getColor() const;

        private:
            /// \brief It's the shape used for the animation.
            sf::RectangleShape _shape;

            /// \brief It's a vector of texture which contains all texture used for the animation.
            std::vector<sf::Texture> _textures;

            /// \brief It's the intern clock used to update the animation.
            sf::Clock _clock;

            /// \brief It's the duration between each frame of the animation.
            /// \note Defines it as millisecond.
            std::size_t _duration;

            /// \brief It keep in memory the texture that is actually used on the shape.
            std::size_t _textureUsed;
    };
} // namespace gui

#endif /* !ANIMATION_HPP_ */
