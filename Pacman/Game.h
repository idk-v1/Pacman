#pragma once
#include <vector>
#include <fstream>

#include "Pacman.h"

class Game
{
public:
	Game();

	void load(std::string);

	void drawMap(sf::RenderWindow&);

	void drawPac(sf::RenderWindow&);

	void movePac();

	void setPacDir(char);

private:
	bool loadMap(std::string);

	void loadFailedMap();

	char map[31][28];

	sf::VertexArray vertMap;

	sf::Vector2i size = { 28, 31 };

	int lives = 3;

	Pacman pac;

	sf::Texture tex;
};

