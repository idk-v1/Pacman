#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Pacman
{
public:
	Pacman();
	Pacman(sf::Texture&);

	void move(char[31][28], sf::Vector2i, int&, bool&, int, int&);

	void draw(sf::RenderWindow&, sf::Vector2i, int);

	void setDir(char);

	sf::Vector2f getPos();

	void reset(sf::Texture&);

	char getDir();

	void die();

	bool needsRestart();

	bool isDead();

private:
	char getTile(char[31][28], int, int);

	void setTile(char[31][28], int, int, char);

	bool canMove(char[31][28], int, int);

	sf::RectangleShape rect;
	sf::Texture texture;
	sf::Vector2f pos = { 13.5f, 23.f }, oldPos = pos;

	sf::Sound sound;
	sf::SoundBuffer chomp, death;

	float speed = 0.08f;

	int restart = 0, deathAnStart = -1, dir = 3, nextDir = 3; // 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT

	bool dead = false, requestRestart = false;
};