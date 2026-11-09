#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable
{
public:
    Paddle(float x, float y);

    void moveUp(float dt);
    void moveDown(float dt);
    void constrainToWindow(float windowHeight);

    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    float getWidth() const { return shape.getSize().x; }

private:
    float width{15.f};
    float height{100.f};
    float speed{500.f};
    sf::Color color{sf::Color::White};
    sf::RectangleShape shape;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif