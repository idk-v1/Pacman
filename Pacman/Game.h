#pragma once
#include <vector>
#include <fstream>

#include "Ghost.h"
#include "RedGhost.h"

class Game
{
public:
	Game(sf::Font&);

	Game();

	void load(int);

	void drawMap(sf::RenderWindow&);

	void drawPac(sf::RenderWindow&);

	void drawGhost(sf::RenderWindow&);

	void movePac();

	void moveGhosts();

	void setPacDir(char);

	char isOver(); // 0 = Not done, 1 = Win, 2 = Lose

private:
	bool loadMap(std::string);

	void loadFailedMap();

	char map[31][28] = { 0 };

	sf::VertexArray vertMap;

	sf::Vector2i size = { 28, 31 };

	int lives = 3;

	Pacman pac;

	sf::Texture tex;

	int dots = 244;

	std::vector<Ghost*> ghosts;

	sf::Text text;

	char over = 0;

	bool failedMap = false;

	int timer = 0, ticks = 0, phaseTimer = 0, phase = 0;

	bool pacAttack = false;

	int phases[4 * 2];
};

