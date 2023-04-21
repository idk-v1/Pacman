//http://gameinternals.com/understanding-pac-man-ghost-behavior


#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Pacman.h"

class Ghost
{
public:
	Ghost();

	void move(char[31][28], sf::Vector2i);

	void draw(sf::RenderWindow&, sf::Vector2i);

	sf::Vector2f getPos();

	void leaveHouse();

	void setMode(char);

	virtual void setTarget(std::vector<Ghost*>&, Pacman&);

	virtual void reset();

	char getMode();

	int getDotReq();

protected:
	char getTile(char[31][28], int, int);

	void setTile(char[31][28], int, int, char);

	bool canMove(char[31][28], int, int);

	sf::RectangleShape rect;

	sf::Vector2f pos, target, scatterPos;

	float speed = 0.1f;

	char dir = 3;

	char mode = -1;

	float width = 1.f;

	sf::Color color;

	int dotReq;

	int restart = 60 * 2;
};

