#pragma once
#include <fstream>

#include "RedGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"
#include "BlueGhost.h"

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

	void update();

	void setPacDir(char);

	int getLives();

	void setLives(int);

	char isOver(); // 0 = Not done, 1 = Win, 2 = Lose

private:
	bool loadMap(std::string);

	void loadFailedMap();

	sf::VertexArray vertMap;
	sf::Vector2i size = { 28, 31 };
	sf::Texture tex, ghostTex, pacTex, *lifeTex;
	sf::Text text;
	sf::RectangleShape rect, debugTarget;

	Pacman* pac;
	Ghost* ghosts[4];

	int phases[8], restart = 2 * 45, lives = 3, dots = 0, timer = 0, ticks = 0, phaseTimer = 0, phase = 0;

	char map[31][28] = { 0 }, over = 0;

	bool failedMap = false, pacAttack = false;
};

