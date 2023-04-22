#include "RedGhost.h"

RedGhost::RedGhost()
{
	color = sf::Color(0xFF0000FF);
	pos = { 13, 11 };
	target = { 13.5, 23 };
	scatterPos = { 28, 0 };
	mode = 1;
	dotReq = 0;
	restart = 60 * 2;
	inBox = false;
}

void RedGhost::setTarget(std::vector<Ghost*>& ghosts, Pacman& pac)
{
	switch (mode)
	{
	case 0:
		target = pac.getPos();
		break;
	case 1:
		target = scatterPos;
	}
}

void RedGhost::reset(bool inBox)
{
	*this = RedGhost();
	if (inBox)
	{
		this->inBox = true;
		this->pos = { 13,15 };
	}
}