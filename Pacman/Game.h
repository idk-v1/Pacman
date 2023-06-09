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

	void load(int, int);

	void drawMap(sf::RenderWindow&, int);

	void drawPac(sf::RenderWindow&);

	void drawGhost(sf::RenderWindow&);

	void movePac(int);

	void moveGhosts();

	void update(int);

	void setPacDir(char);

	int getLives();

	void setLives(int);

	char isOver(); // 0 = Not done, 1 = Win, 2 = Lose

	int getScore();

	void setScore(int);

private:
	bool loadMap(std::string);

	void loadFailedMap();

	sf::VertexArray vertMap;
	sf::Vector2i size = { 28, 31 };
	sf::Texture tex, ghostTex, pacTex, *lifeTex, *fruitTex;
	sf::Text text;
	sf::RectangleShape rect, debugTarget, fruitRect;

	sf::Sound sound;
	sf::SoundBuffer eatFruit, eatGhost, intro;

	Pacman* pac;
	Ghost* ghosts[4];

	std::fstream file;

	int phases[8], restart, lives = 3, dots = 0, timer = 0, ticks = 0,
		phaseTimer = 0, phase = 0, level, score = 0, ghostsEaten = 0,
		fruitTimer = 0, fruit = 0, highScore = 0, overCount;

	char map[31][28] = { 0 }, over = 0;

	bool failedMap = false, pacAttack = false, ended = false;
};