#pragma once
#include <SFML/Graphics.hpp>

#include "Game.h"

class Window
{
public:
	Window(int, int);

	void start();
private:
	void update();

	void render();

	sf::RenderWindow w;

	sf::View view;

	sf::Clock clock;

	int lag = 0;

	Game game;
};

