#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Pacman
{
public:
	Pacman();

	void move(char[31][28], sf::Vector2i, int&, bool&);

	void draw(sf::RenderWindow&, sf::Vector2i);

	void setDir(char);

	sf::Vector2f getPos();

	void reset();

private:
	char getTile(char[31][28], int, int);

	void setTile(char[31][28], int, int, char);

	bool canMove(char[31][28], int, int);

	sf::Vector2f pos = {13.5f, 23.f};

	float speed = 0.0975f;

	int dir = 3, nextDir = 3; // 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT

	float width = 1.f;

	sf::RectangleShape rect;
};

