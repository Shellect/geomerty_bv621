#include "Ball.h"
#include "TextureLoadException.h"
#include <SFML/Graphics.hpp>
#include <corecrt_math_defines.h>
#include <iostream>

Ball::Ball(const std::string &imagePath, float x, float y)
    : respawnX(x), respawnY(y)
{
    if (!texture.loadFromFile(imagePath))
    {
        throw TextureLoadException(imagePath);
    }
    sprite.emplace(texture);
    sf::Vector2f size = sprite->getLocalBounds().size;
    sprite->setOrigin({size.x / 2.f, size.y / 2.f});
    constexpr float ballSize = 24.f;
    sprite->setScale({ballSize / size.x, ballSize / size.y});
    reset(1.f);
}

CollisionType Ball::handleCollision(const sf::FloatRect &leftPaddleBounds, const sf::FloatRect &rightPaddleBounds, float fieldWidth, float fieldHeight)
{
    sf::FloatRect b = sprite->getGlobalBounds();

    // 1. Стены — приоритет, чтобы вытолкнуть мяч из угла
    if (b.position.y <= 0.f)
    {
        sprite->setPosition({b.position.x, b.size.y / 2.f + 1.f});
        velocity.y = std::abs(velocity.y);
        return CollisionType::None;
    } else if (b.position.y + b.size.y >= fieldHeight)
    {
        sprite->setPosition({b.position.x, fieldHeight - b.size.y / 2.f - 1.f});
        velocity.y = -std::abs(velocity.y);
        return CollisionType::None;
    } else if (b.position.x <= 0.f)
    {
        sprite->setPosition({b.size.x / 2.f + 1.f, b.position.y});
        velocity.x = std::abs(velocity.x);
        return CollisionType::WallLeft;
    } else if (b.position.x + b.size.x >= fieldWidth)
    {
        sprite->setPosition({fieldWidth - b.size.x / 2.f - 1.f, b.position.y});
        velocity.x = -std::abs(velocity.x);
        return CollisionType::WallRight;
    } else if (b.findIntersection(leftPaddleBounds))
    {
        sprite->setPosition({leftPaddleBounds.position.x + leftPaddleBounds.size.x + b.size.x / 2 + 1.f, b.position.y});
        collidePaddle(leftPaddleBounds);
        velocity.x = std::abs(velocity.x);
    } else if (b.findIntersection(rightPaddleBounds))
    {
        sprite->setPosition({rightPaddleBounds.position.x - b.size.x / 2.f - 1.f, b.position.y});
        collidePaddle(rightPaddleBounds);
        velocity.x = -std::abs(velocity.x);
    }
    return CollisionType::None;
}

void Ball::collidePaddle(const sf::FloatRect &paddleBounds)
{
    // Угол отскока от точки удара
    float ballCenterY = sprite->getPosition().y;
    float paddleCenterY = paddleBounds.position.y + paddleBounds.size.y / 2.f;
    float offset = std::clamp((ballCenterY - paddleCenterY) / (paddleBounds.size.y / 2.f), -1.f, 1.f);
    float angle = offset * 60.f * M_PI / 180.f;
    float currentSpeed = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
    velocity = {std::cos(angle) * currentSpeed, std::sin(angle)* currentSpeed};
}

float Ball::randomAngleRad()
{
    // Угол в диапазоне [-60°, +60°] — мяч не летит почти вертикально
    std::uniform_real_distribution<float> dist(-60.f, 60.f);
    return dist(rng) * M_PI / 180.f;
}

void Ball::reset(float direction)
{
    sprite->setPosition({respawnX, respawnY});
    float angle = randomAngleRad();
    velocity = {std::cos(angle) * speed * direction, std::sin(angle) * speed};
}

void Ball::update(float dt)
{
    sprite->move(velocity * dt);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // states содержит трансформации/шейдеры, переданные в window.draw
    target.draw(*sprite, states);
}