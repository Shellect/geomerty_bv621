#include "Ball.h"
#include "TextureLoadException.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Ball::Ball(std::string &imagePath, float x, float y)
    : sprite(texture), respawnX(x), respawnY(y)
{
    if (!texture.loadFromFile(imagePath))
    {
        throw TextureLoadException(imagePath);
    }
    sf::Vector2f size = sprite.getLocalBounds().size;
    sprite.setOrigin({size.x / 2.f, size.y / 2.f});
    reset();
}

float Ball::randomAngleRad()
{
    // Угол в диапазоне [-60°, +60°] — мяч не летит почти вертикально
    std::uniform_real_distribution<float> dist(-60.f, 60.f);
    return dist(rng) * M_PI / 180.f;
}

void Ball::reset()
{
    sprite.setPosition({respawnX, respawnY});
    float angle = randomAngleRad();
    velocity.x = std::cos(angle) * speed * direction;
    velocity.y = std::sin(angle) * speed;
}

void Ball::update(float dt)
{
    sprite.move(velocity * dt);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // states содержит трансформации/шейдеры, переданные в window.draw
    target.draw(sprite, states);
}

void Ball::bounce()
{
    
}
