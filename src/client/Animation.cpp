/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** Animation
*/


#include "Animation.hpp"

using namespace anim;

Animation::Animation()
{
    _textures.clear();
    _clock.restart();
    _duration = 0;
    _textureUsed = 0;
}

void Animation::update()
{
    if (std::size_t(_clock.getElapsedTime().asMilliseconds()) > _duration) {
        _textureUsed++;
        if (_textureUsed >= _textures.size())
            _textureUsed = 0;
        _shape.setTexture(&_textures[_textureUsed]);
        _clock.restart();
    }
}

void Animation::addTexture(const std::string &texturePath, const sf::Vector2f &position, const sf::Vector2f &size)
{
    sf::Image image;

    if (!image.loadFromFile(texturePath))
        return;
    addTexture(image, position, size);
}

void Animation::addTexture(const sf::Image &image, const sf::Vector2f &position, const sf::Vector2f &size)
{
    sf::Texture texture;
    sf::IntRect texture_rect;

    texture_rect.left = position.x;
    texture_rect.top = position.y;
    texture_rect.width = size.x;
    texture_rect.height = size.y;
    if (!texture.loadFromImage(image, texture_rect))
        return;
    _textures.push_back(texture);
    _shape.setTexture(&_textures.back());
}

void Animation::moveShape(const sf::Vector2f &offset)
{
    _shape.move(offset);
}

const sf::RectangleShape &Animation::getShape() const
{
    return _shape;
}

void Animation::setDuration(const std::size_t &duration)
{
    _duration = duration;
}

const std::size_t &Animation::getDuration() const
{
    return _duration;
}

void Animation::setPosition(const sf::Vector2f &position)
{
    _shape.setPosition(position);
}

const sf::Vector2f &Animation::getPosition() const
{
    return _shape.getPosition();
}

void Animation::setSize(const sf::Vector2f &size)
{
    _shape.setSize(size);
}

const sf::Vector2f &Animation::getSize() const
{
    return _shape.getSize();
}

const sf::FloatRect Animation::getGlobalBounds()
{
    return _shape.getGlobalBounds();
}

void Animation::setColor(const sf::Color &color)
{
    _shape.setFillColor(color);
}

const sf::Color &Animation::getColor() const
{
    return _shape.getFillColor();
}
