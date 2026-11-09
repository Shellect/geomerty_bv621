#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Paddle.h"
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow window;
	Ball ball;
	Paddle leftPaddle;
	Paddle rightPaddle;

	int leftScore = 0;
	int rightScore = 0;

public:
	Game();
	void run();
};
#endif