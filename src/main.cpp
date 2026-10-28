#include "Rectangle.h"
#include <optional>
#include <SFML/Graphics.hpp>

int main()
{ 
    // x/y = 200,200; ширина - 100px; высота - 50px
    // Rectangle r{200, 200, 100, 50};

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f));
    rectangle.setFillColor(sf::Color(10, 186, 181, 255));
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(2.f);
    rectangle.setPosition({200, 200});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black); // очистка фона
        window.draw(rectangle);         // рисуем прямоугольник
        window.display();               // показываем кадр
    }

    return 0;
}