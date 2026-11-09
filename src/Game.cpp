#include "Game.h"

Game::Game()
    : window(sf::VideoMode({800, 600}), "Pong"),
      ball("img/ball.png", 400.f, 300.f),
      leftPaddle(20.f, 250.f),
      rightPaddle(765.f, 250.f)
{
}

void Game::run()
{
    // Часы для расчета времени
    sf::Clock clock;

    while (window.isOpen())
    {
        // SFML 3: pollEvent возвращает std::optional<sf::Event>
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float dt = clock.restart().asSeconds();

        // Ввод
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            leftPaddle.moveUp(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            leftPaddle.moveDown(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            rightPaddle.moveUp(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            rightPaddle.moveDown(dt);
        leftPaddle.constrainToWindow(600);
        rightPaddle.constrainToWindow(600);

        // Логика мяча
        ball.update(dt);
        CollisionType type = ball.handleCollision(leftPaddle.getBounds(), rightPaddle.getBounds(), 800, 600);
        if (type == CollisionType::WallLeft)
        {
            ++rightScore;
        } else if (type == CollisionType::WallRight)
        {
            ++leftScore;
        }
        

        // Отрисовка
        window.clear(sf::Color::Black); // очистка фона
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.display(); // показываем кадр
    }
}