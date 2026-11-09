#include "Game.h"
#include <stdexcept>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

Game::Game()
    : window(sf::VideoMode({800, 600}), "Pong"),
      ball("img/ball.png", 400.f, 300.f),
      leftPaddle(20.f, 250.f),
      rightPaddle(765.f, 250.f)
{
    centerWindowOnCursorScreen();

    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        throw std::runtime_error("Failed to load font");

    scoreText.emplace(font);
    scoreText->setCharacterSize(48);
    scoreText->setFillColor(sf::Color::White);
    updateScoreText();
}

void Game::centerWindowOnCursorScreen()
{
    POINT cursor{};
    GetCursorPos(&cursor);
    HMONITOR monitor = MonitorFromPoint(cursor, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO info{};
    info.cbSize = sizeof(info);
    if (!GetMonitorInfo(monitor, &info))
        return;

    constexpr int width = 800;
    constexpr int height = 600;
    int x = info.rcMonitor.left + (info.rcMonitor.right - info.rcMonitor.left - width) / 2;
    int y = info.rcMonitor.top + (info.rcMonitor.bottom - info.rcMonitor.top - height) / 2;
    window.setPosition({x, y});
}

void Game::updateScoreText()
{
    scoreText->setString(std::to_string(leftScore) + "  :  " + std::to_string(rightScore));
    sf::FloatRect bounds = scoreText->getLocalBounds();
    scoreText->setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y});
    scoreText->setPosition({400.f, 16.f});
}

void Game::run()
{
    // Часы для расчета времени
    sf::Clock clock;

    bool running = true;
    while (running && window.isOpen())
    {
        // SFML 3: pollEvent возвращает std::optional<sf::Event>
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                running = false;
        }
        if (!running || !window.isOpen())
            break;

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
            updateScoreText();
            ball.reset(-1.f);
        } else if (type == CollisionType::WallRight)
        {
            ++leftScore;
            updateScoreText();
            ball.reset(1.f);
        }
        

        // Отрисовка
        window.clear(sf::Color::Black); // очистка фона
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.draw(*scoreText);
        window.display(); // показываем кадр
    }
}