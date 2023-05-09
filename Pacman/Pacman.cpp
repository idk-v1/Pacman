#include "Pacman.h"


Pacman::Pacman()
{

}

Pacman::Pacman(sf::Texture &tex)
{
	texture = tex;
	rect.setTexture(&texture);
	rect.setTextureRect(sf::IntRect(2 * 14, dir * 14, 14, 14));
}

void Pacman::move(char map[31][28], sf::Vector2i size, int &dots, bool &canAttack, int level, int &score)
{
	float speed = this->speed;

	if (level < 1)
		speed = 0.08;
	else if (level < 4)
		speed = 0.09;
	else if (level < 20)
		speed = 0.1;
	else speed = 0.09;

	oldPos = pos;

	if (restart == 0)
	{
		// change direction if able
		switch (nextDir)
		{
		case 0:
			if (canMove(map, pos.x, pos.y - speed) && canMove(map, pos.x + 0.9, pos.y - speed))
				dir = nextDir;
			break;
		case 1:
			if (canMove(map, pos.x + speed + 1, pos.y) && canMove(map, pos.x + speed + 1, pos.y + 0.9))
				dir = nextDir;
			break;
		case 2:
			if (canMove(map, pos.x, pos.y + speed + 1) && canMove(map, pos.x + 0.9, pos.y + speed + 1))
				dir = nextDir;
			break;
		case 3:
			if (canMove(map, pos.x - speed, pos.y) && canMove(map, pos.x - speed, pos.y + 0.9))
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
			if (canMove(map, pos.x, pos.y - speed))
				pos.y -= speed;
			else
				pos.y = std::round(pos.y);
			break;
		case 1:
			if (canMove(map, pos.x + 0.99 + speed, pos.y))
				pos.x += speed;
			else
				pos.x = std::round(pos.x);
			break;
		case 2:
			if (canMove(map, pos.x, pos.y + 0.99 + speed))
				pos.y += speed;
			else
				pos.y = std::round(pos.y);
			break;
		case 3:
			if (canMove(map, pos.x - speed, pos.y))
				pos.x -= speed;
			else
				pos.x = std::round(pos.x);
		}

		if (getTile(map, pos.x + 0.49, pos.y + 0.49) == 0x20)
		{
			dots--;
			score += 10;
			setTile(map, pos.x + 0.49, pos.y + 0.49, 0);
		}
		else if (getTile(map, pos.x + 0.49, pos.y + 0.49) == 0x21)
		{
			dots--;
			score += 50;
			setTile(map, pos.x + 0.49, pos.y + 0.49, 0);
			canAttack = true;
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
	else
		restart--;
}

void Pacman::draw(sf::RenderWindow &w, sf::Vector2i size, int ticks)
{
	float minScale = std::min(w.getSize().x / (float)size.x, w.getSize().y / (float)(size.y + 2 + 3));
	float xoff = (w.getSize().x - size.x * minScale) / 2.f;
	float yoff = (w.getSize().y - (size.y - 2) * minScale) / 2.f;

	if (pos != oldPos)
		rect.setTextureRect(sf::IntRect(ticks / 4 % 4 * 14, dir * 14, 14, 14));
	rect.setSize(sf::Vector2f(minScale * 1.5, minScale * 1.5));
	rect.setPosition(xoff + pos.x * minScale - minScale * 0.25, yoff + pos.y * minScale - minScale * 0.25);
	w.draw(rect);
}

void Pacman::setDir(char newDir)
{
	nextDir = newDir;
}

sf::Vector2f Pacman::getPos()
{
	return pos;
}

char Pacman::getTile(char map[31][28], int x, int y)
{
	if (!(x < 0 || y < 0 || x >= 28 || y >= 31))
		return map[y][x];
	return -1;
}

void Pacman::setTile(char map[31][28], int x, int y, char val)
{
	if (!(x < 0 || y < 0 || x >= 28 || y >= 31))
		map[y][x] = val;
}

bool Pacman::canMove(char map[31][28], int x, int y)
{
	switch (getTile(map, x, y))
	{
	case 0x00:
	case 0x20:
	case 0x21:
	case -1:
		return true;
	default:
		return false;
	}
}

void Pacman::reset(sf::Texture &tex)
{
	*this = Pacman(tex);
	texture = tex;
	rect.setTexture(&texture);
}

char Pacman::getDir()
{
	return dir;
}