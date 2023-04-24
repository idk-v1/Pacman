#include "OrangeGhost.h"

OrangeGhost::OrangeGhost()
{
	color = sf::Color(0xFF8800FF);
	pos = { 12, 15 };
	target = { 13, 11 };
	scatterPos = { 0, 31 };
	mode = 1;
	dotReq = 81;
}

void OrangeGhost::setTarget(std::vector<Ghost*>& ghosts, Pacman& pac)
{
	switch (mode)
	{
	case 0:
		if (std::sqrt(std::pow(int(pos.x + 0.49) - target.x, 2) + std::pow(int(pos.y + 0.49 - 1) - target.y, 2)) > 8)
			switch (pac.getDir())
			{
			case 0:
				target = { pac.getPos().x, pac.getPos().y };
				break;
			case 1:
				target = { pac.getPos().x, pac.getPos().y };
				break;
			case 2:
				target = { pac.getPos().x, pac.getPos().y };
				break;
			case 3:
				target = { pac.getPos().x, pac.getPos().y };
				break;
			}
		else
			target = scatterPos;
		break;
	case 1:
		target = scatterPos;
	}
}

void OrangeGhost::reset(bool)
{
	*this = OrangeGhost();
	if (inBox)
		this->pos = { 13,15 };
}