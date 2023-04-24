#include "RedGhost.h"

RedGhost::RedGhost()
{
	color = sf::Color(0xFF0000FF);
	pos = { 13, 11 };
	target = { 13.5, 23 };
	scatterPos = { 28, 0 };
	mode = 1;
	dotReq = 0;
}

void RedGhost::setTarget(Ghost* red, Pacman& pac)
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
		this->pos = { 13,15 };
}