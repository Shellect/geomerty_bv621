#include "Paddle.h"

Paddle::Paddle(float x, float y)
    : shape(sf::Vector2f(width, height))
{
    shape.setPosition({x, y});
    shape.setFillColor(color);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}

void Paddle::moveUp(float dt)
{
    shape.move({0.f, -speed * dt});
}

void Paddle::moveDown(float dt)
{
    shape.move({0.f, speed * dt});
}

void Paddle::constrainToWindow(float windowHeight)
{
    sf::Vector2f pos = shape.getPosition();
    if (pos.y < 0.f)
        shape.setPosition({pos.x, 0.f});
    if (pos.y + shape.getSize().y > windowHeight)
        shape.setPosition({pos.x, windowHeight - shape.getSize().y});
}