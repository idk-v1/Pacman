#include "Pacman.h"

Pacman::Pacman()
{
	rect.setFillColor(sf::Color(0xFFFF00FF));

	for (int i = 0; i < 4; i++)
		col[i].setFillColor(sf::Color(0xFFFFFF3F));
}

void Pacman::move(char map[31][28], sf::Vector2i size)
{
	sf::Vector2f oldPos = pos;
	dir = nextDir;

	switch (dir)
	{
	case 0:
		if (!getTile(map, pos.x, pos.y))
			pos.y -= speed;
		break;
	case 1:
		if (!getTile(map, pos.x + 0.99, pos.y))
			pos.x += speed;
		break;
	case 2:
		if (!getTile(map, pos.x, pos.y + 0.99))
			pos.y += speed;
		break;
	case 3:
		if (!getTile(map, pos.x, pos.y))
			pos.x -= speed;
	}

	if (dir % 2)
		pos.y = std::round(pos.y);
	else
		pos.x = std::round(pos.x);

	if (pos.x < 0)
		pos.x += size.x;
	if (pos.y < 0)
		pos.y += size.y;
	if (pos.x >= size.x)
		pos.x -= size.x;
	if (pos.y >= size.y)
		pos.y -= size.y;

	for (int i = 0; i < 4; i++)
	{
		colPos[i] = sf::Vector2i(int(pos.x + 0.99 * (i % 2)), int(pos.y + 0.99 * (i / 2)));
	}
}

void Pacman::draw(sf::RenderWindow &w, sf::Vector2i size)
{
	float minScale = std::min(w.getSize().x / (float)size.x, w.getSize().y / (float)size.y);
	float xoff = (w.getSize().x - size.x * minScale) / 2.f;
	float yoff = (w.getSize().y - size.y * minScale) / 2.f;

	rect.setSize(sf::Vector2f(width * minScale, width * minScale));
	//rect.setOrigin(minScale * 0.5, minScale * 0.5);
	rect.setPosition(xoff + pos.x * minScale, yoff + pos.y * minScale);
	w.draw(rect);

	for (int i = 0; i < 4; i++)
	{
		col[i].setPosition(xoff + colPos[i].x * minScale, yoff + colPos[i].y * minScale);
		col[i].setSize(sf::Vector2f(minScale, minScale));
		w.draw(col[i]);
	}
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
