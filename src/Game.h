#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include <optional>

class Game
{
private:
	sf::RenderWindow window;
	Ball ball;
	Paddle leftPaddle;
	Paddle rightPaddle;

	int leftScore = 0;
	int rightScore = 0;
	sf::Font font;
	std::optional<sf::Text> scoreText;

	void updateScoreText();
	void centerWindowOnCursorScreen();

public:
	Game();
	void run();
};
#endif