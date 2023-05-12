#include "Ghost.h"

Ghost::Ghost()
{
	pos = { 13, 11 };
	target = pos;
	scatterPos = pos;
	dotReq = 100;
	mode = 1;
}

bool Ghost::isInBox()
{
	return inBox;
}

void Ghost::setBlink(bool val)
{
	blink = val;
}

void Ghost::die()
{
	dir = (dir + 2) % 4;
	dead = true;
}

bool Ghost::isDead()
{
	return dead;
}

bool Ghost::needsRestart()
{
	return requestRestart;
}

void Ghost::move(char map[31][28], sf::Vector2i size, int level)
{
	float speed = this->speed;

	if (mode == 2)
	{
		if (level < 1)
			speed = 0.05;
		else if (level < 4)
			speed = 0.055;
		else
			speed = 0.06;
	}

	if (getTile(map, pos.x, pos.y + 1) == 0x05 && getTile(map, pos.x, pos.y - 1) == 0x05)
	{
		if (level < 1)
			speed = 0.04;
		else if (level < 4)
			speed = 0.045;
		else
			speed = 0.05;
	}

	if (dead)
		speed = 0.15;

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

	if (pos.x < 0)
		pos.x += size.x;
	if (pos.y < 0)
		pos.y += size.y;
	if (pos.x >= size.x)
		pos.x -= size.x;
	if (pos.y >= size.y)
		pos.y -= size.y;
}

void Ghost::update(char map[31][28], sf::Vector2i size, int level)
{
	if (level < 1)
		speed = 0.075f;
	else if (level < 4)
		speed = 0.085f;
	else
		speed = 0.095f;

	if (dead)
	{
		if (pos.x > 13 && pos.x < 14)
		{
			if (pos.y == 11 && moveEnabled)
				moveEnabled = false;
			else if (!moveEnabled)
			{
				if (pos.y < 14)
					pos.y += speed;
				else
					requestRestart = true;
			}
		}
	}

	if (restart == 0 && moveEnabled)
	{
		if (inBox)
		{
			if (pos.x < 13)
				pos.x += speed;
			else if (pos.x > 14)
				pos.x -= speed;
			else
				pos.y -= speed;
			if (pos.y <= 11)
				inBox = false;
		}
		else
		{
			if (turnCd == 0)
				turn(map, size);
			else
				turnCd--;
			move(map, size, level);
		}
	}
	else
		restart--;
}

void Ghost::turn(char map[31][28], sf::Vector2i size)
{
	float dist = 99999.f, tmpDist = -1;
	char newDir = -1, randDir = rand() % 4;

	if (dir != 2)
		if (canMove(map, pos.x, pos.y - speed * 4) && canMove(map, pos.x + 0.9, pos.y - speed * 4))
		{
			tmpDist = std::sqrt(std::pow(int(pos.x + 0.49) - target.x, 2) + std::pow(int(pos.y + 0.49 - 1) - target.y, 2));
			if (tmpDist < dist || randDir * (mode == 2) == 0)
			{
				newDir = 0;
				dist = tmpDist;
			}
		}
	if (dir != 3)
		if (canMove(map, pos.x + speed * 4 + 1, pos.y) && canMove(map, pos.x + speed * 4 + 1, pos.y + 0.9))
		{
			tmpDist = std::sqrt(std::pow(int(pos.x + 0.49 + 1) - target.x, 2) + std::pow(int(pos.y + 0.49) - target.y, 2));
			if (tmpDist < dist || randDir * (mode == 2) == 1)
			{
				newDir = 1;
				dist = tmpDist;
			}
		}
	if (dir != 0)
		if (canMove(map, pos.x, pos.y + speed * 4 + 1) && canMove(map, pos.x + 0.9, pos.y + speed * 4 + 1))
		{
			tmpDist = std::sqrt(std::pow(int(pos.x + 0.49) - target.x, 2) + std::pow(int(pos.y + 0.49 + 1) - target.y, 2));
			if (tmpDist < dist || randDir * (mode == 2) == 2)
			{
				newDir = 2;
				dist = tmpDist;
			}
		}
	if (dir != 1)
		if (canMove(map, pos.x - speed * 4, pos.y) && canMove(map, pos.x - speed * 4, pos.y + 0.9))
		{
			tmpDist = std::sqrt(std::pow(int(pos.x + 0.49 - 1) - target.x, 2) + std::pow(int(pos.y + 0.49) - target.y, 2));
			if (tmpDist < dist || randDir * (mode == 2) == 3)
			{
				newDir = 3;
				dist = tmpDist;
			}
		}
	if (dir % 2 != newDir % 2)
		turnCd = 2;

	if (newDir != -1)
		dir = newDir;

	if (dir % 2)
		pos.y = std::round(pos.y);
	else
		pos.x = std::round(pos.x);
}

void Ghost::draw(sf::RenderWindow &w, sf::Vector2i size, int timer)
{
	float minScale = std::min(w.getSize().x / (float)size.x, w.getSize().y / (float)(size.y + 2 + 3));
	float xoff = (w.getSize().x - size.x * minScale) / 2.f;
	float yoff = (w.getSize().y - (size.y - 2) * minScale) / 2.f;

	rect.setTextureRect(sf::IntRect(texXOff * 14, dir * 14, 14, 14));

	if (mode == 2)
		if (timer > 45 * 2.5 || timer / 7 % 2 == 0)
			rect.setTextureRect(sf::IntRect(4 * 14, dir * 14, 14, 14));

	if (dead)
		rect.setTextureRect(sf::IntRect(5 * 14, dir * 14, 14, 14));

	rect.setSize(sf::Vector2f(minScale * 1.5, minScale * 1.5));
	rect.setPosition(xoff + pos.x * minScale - minScale * 0.25, yoff + pos.y * minScale - minScale * 0.25);
	w.draw(rect);
}

sf::Vector2f Ghost::getPos()
{
	return pos;
}

void Ghost::leaveHouse()
{
	target = { 13, 11 };
}

void Ghost::setMode(char newMode, int level)
{
	if (!(mode == 2 && newMode < 2) && newMode != mode)
		dir = (dir + 2) % 4;
	if (level < 20 || newMode != 2)
		mode = newMode;
}

void Ghost::setTarget(Ghost* red, Pacman& pac)
{
	switch (mode)
	{
	case 1:
		target = scatterPos;
		break;
	}
}

sf::Vector2f Ghost::getTarget()
{
	return target;
}

char Ghost::getTile(char map[31][28], int x, int y)
{
	if (x < 0 || y < 0 || x >= 28 || y >= 31)
		return -1;
	return map[y][x];
}

void Ghost::setTile(char map[31][28], int x, int y, char val)
{
	if (x < 0 || y < 0 || x >= 28 || y >= 31);
	else
		map[y][x] = val;
}

bool Ghost::canMove(char map[31][28], int x, int y)
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

void Ghost::reset(sf::Texture &tex, bool inBox)
{
	*this = Ghost();
	if (inBox)
		this->pos = { 13,15 };
}

char Ghost::getMode()
{
	return mode;
}

int Ghost::getDotReq()
{
	return dotReq;
}

void Ghost::enableMove(bool val)
{
	moveEnabled = val;
}