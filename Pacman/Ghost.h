//http://gameinternals.com/understanding-pac-man-ghost-behavior
//https://www.gamedeveloper.com/design/the-pac-man-dossier


#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Pacman.h"

class Ghost
{
public:
	Ghost();

	void update(char[31][28], sf::Vector2i);

	void draw(sf::RenderWindow&, sf::Vector2i);

	sf::Vector2f getPos();

	void leaveHouse();

	void setMode(char);

	virtual void setTarget(Ghost*, Pacman&);

	virtual void reset(bool);

	void enableMove(bool);

	char getMode();

	int getDotReq();

	bool isInBox();

protected:
	void move(char[31][28], sf::Vector2i);

	void turn(char[31][28], sf::Vector2i);

	char getTile(char[31][28], int, int);

	void setTile(char[31][28], int, int, char);

	bool canMove(char[31][28], int, int);

	sf::RectangleShape rect;

	sf::Vector2f pos, target, scatterPos;

	float speed = 0.1f;

	char dir = 3;

	char mode = 1;

	float width = 1.f;

	sf::Color color;

	int dotReq;

	int restart = 45 * 2;

	bool inBox = true;

	int turnCd = 0;

	bool moveEnabled = false;
};

