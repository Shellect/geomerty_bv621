#ifndef BALL
#define BALL

#include <SFML/Graphics.hpp>
#include <optional>
#include <random>
#include <string>
#include "Collision.h"

class Ball : public sf::Drawable
{
private:
    float respawnX{0.f};
    float respawnY{0.f};
    float speed = 300.f;                      // базовая скорость мяча
    std::mt19937 rng{std::random_device{}()}; // ГПСЧ
    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    sf::Vector2f velocity{300.f, 220.f};

    // Переопределяем отрисовку
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    float randomAngleRad();
    void collidePaddle(const sf::FloatRect &paddleBounds);

public:
    Ball(const std::string &imagePath, float x, float y);
    CollisionType handleCollision(const sf::FloatRect &leftPaddleBounds,
                                  const sf::FloatRect &rightPaddleBounds,
                                  float fieldWidth,
                                  float fieldHeight);

    void reset(float direction);
    void update(float dt);
};
#endif