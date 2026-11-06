#ifndef BALL
#define BALL

#include <SFML/Graphics.hpp>
#include <random>
#include <string>

class Ball : public sf::Drawable
{
private:
    float respawnX{0.f};
    float respawnY{0.f};
    float direction{1};                       // Направление вправо{1}, влево{-1}
    float speed = 300.f;                      // базовая скорость мяча
    std::mt19937 rng{std::random_device{}()}; // ГПСЧ
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity{300.f, 220.f};
    float randomAngleRad();
    // Переопределяем отрисовку
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    Ball(std::string &imagePath, float x, float y);
    void reset();
    void update(float dt);
    void bounce();
};
#endif