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
	sf::Font font;

	Game game;

	int lag = 0, dir = -1, level = 0, ups = 50;

	bool keys[4] = { false };
};