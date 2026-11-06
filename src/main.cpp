#include "Ball.h"

#include <optional>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");

    // Создаем спрайт
    std::string imagePath = "./img/ball.png";
    Ball ball(imagePath, 400.f, 300.f);

    // Часы для расчета времени
    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // Логика мяча
        float dt = clock.restart().asSeconds();
        ball.update(dt);

        // Отрисовка
        window.clear(sf::Color::Black); // очистка фона
        window.draw(ball);
        window.display(); // показываем кадр
    }

    return 0;
}