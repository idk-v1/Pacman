#include "Pacman.h"

Pacman::Pacman()
{
	rect.setFillColor(sf::Color(0xFFFF00FF));
}

void Pacman::move(char map[31][28], sf::Vector2i size)
{
	// change direction if able
	switch (nextDir)
	{
	case 0:
		if (!getTile(map, pos.x, pos.y - speed) && !getTile(map, pos.x + 0.9, pos.y - speed))
			dir = nextDir;
		break;
	case 1:
		if (!getTile(map, pos.x + speed + 1, pos.y) && !getTile(map, pos.x + speed + 1, pos.y + 0.9))
			dir = nextDir;
		break;
	case 2:
		if (!getTile(map, pos.x, pos.y + speed + 1) && !getTile(map, pos.x + 0.9, pos.y + speed + 1))
			dir = nextDir;
		break;
	case 3:
		if (!getTile(map, pos.x - speed, pos.y) && !getTile(map, pos.x - speed, pos.y + 0.9))
			dir = nextDir;
	}

	if (dir % 2)
		pos.y = std::round(pos.y);
	else
		pos.x = std::round(pos.x);

	// move if not colliding
	switch (dir)
	{
	case 0:
		if (!getTile(map, pos.x, pos.y - speed))
			pos.y -= speed;
		else
			pos.y = std::round(pos.y);
		break;
	case 1:
		if (!getTile(map, pos.x + 0.99 + speed, pos.y))
			pos.x += speed;
		else
			pos.x = std::round(pos.x);
		break;
	case 2:
		if (!getTile(map, pos.x, pos.y + 0.99 + speed))
			pos.y += speed;
		else
			pos.y = std::round(pos.y);
		break;
	case 3:
		if (!getTile(map, pos.x - speed, pos.y))
			pos.x -= speed;
		else
			pos.x = std::round(pos.x);
	}

	if (pos.x < 0)
		pos.x += size.x;
	if (pos.y < 0)
		pos.y += size.y;
	if (pos.x >= size.x)
		pos.x -= size.x;
	if (pos.y >= size.y)
		pos.y -= size.y;
}

void Pacman::draw(sf::RenderWindow &w, sf::Vector2i size)
{
	float minScale = std::min(w.getSize().x / (float)size.x, w.getSize().y / (float)size.y);
	float xoff = (w.getSize().x - size.x * minScale) / 2.f;
	float yoff = (w.getSize().y - size.y * minScale) / 2.f;

	rect.setSize(sf::Vector2f(width * minScale, width * minScale));
	rect.setPosition(xoff + pos.x * minScale, yoff + pos.y * minScale);
	w.draw(rect);
}

void Pacman::setDir(char newDir)
{
	nextDir = newDir;
}

char Pacman::getTile(char map[31][28], int x, int y)
{
	if (x < 0 || y < 0 || x >= 28 || y >= 31)
		return 0;
	return map[y][x];
}
