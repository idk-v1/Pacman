#include "PinkGhost.h"

PinkGhost::PinkGhost()
{
	color = sf::Color(0xFF88FFFF);
	pos = { 13, 15 };
	target = { 13, 11 };
	scatterPos = { 0, 0 };
	mode = 1;
	dotReq = 0;
}

void PinkGhost::setTarget(std::vector<Ghost*>& ghosts, Pacman& pac)
{
	switch (mode)
	{
	case 0:
		switch (pac.getDir())
		{
		case 0:
			target = { pac.getPos().x, pac.getPos().y - 4 };
			break;
		case 1:
			target = { pac.getPos().x + 4, pac.getPos().y };
			break;
		case 2:
			target = { pac.getPos().x, pac.getPos().y + 4 };
			break;
		case 3:
			target = { pac.getPos().x - 4, pac.getPos().y };
			break;
		}
		break;
	case 1:
		target = scatterPos;
	}
}

void PinkGhost::reset(bool)
{
	*this = PinkGhost();
	if (inBox)
		this->pos = { 13,15 };
}