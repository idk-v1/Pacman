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

	void draw(sf::RenderWindow&, sf::Vector2i, int);

	sf::Vector2f getPos();

	void leaveHouse();

	void setMode(char);

	virtual void setTarget(Ghost*, Pacman&);

	sf::Vector2f getTarget();

	virtual void reset(sf::Texture&, bool);

	void enableMove(bool);

	char getMode();

	int getDotReq();

	bool isInBox();

	void setBlink(bool);

protected:
	void move(char[31][28], sf::Vector2i);

	void turn(char[31][28], sf::Vector2i);

	char getTile(char[31][28], int, int);

	void setTile(char[31][28], int, int, char);

	bool canMove(char[31][28], int, int);

	sf::RectangleShape rect;
	sf::Texture texture;
	sf::Vector2f pos, target, scatterPos;

	int texXOff;

	float speed = 0.09f;

	int dotReq, turnCd = 0, restart = 2 * 45;

	char dir = 3, mode = 1;

	bool inBox = true, moveEnabled = false, blink = false;
};

