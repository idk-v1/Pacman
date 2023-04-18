#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Pacman
{
public:
	Pacman();

	void move(char[31][28], sf::Vector2i);

	void draw(sf::RenderWindow&, sf::Vector2i);

	void setDir(char);

	char getTile(char[31][28], int, int);

private:
	sf::Vector2f pos = {13.5f, 23.f};

	float speed = 0.095f;

	int dir = 3, nextDir = 3; // 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT

	bool canAttack = false;

	int res = 20;

	float width = 1.f;

	sf::RectangleShape rect;
};

