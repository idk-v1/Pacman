#include "BlueGhost.h"

BlueGhost::BlueGhost()
{
	color = sf::Color(0x00FFFFFF);
	pos = { 14, 15 };
	target = { 13, 11 };
	scatterPos = { 28, 31 };
	mode = 1;
	dotReq = 30;
}

void BlueGhost::setTarget(Ghost* red, Pacman& pac)
{
	switch (mode)
	{
	case 0:
		switch (pac.getDir())
		{
		case 0:
			target = { pac.getPos().x, pac.getPos().y - 2 };
			break;
		case 1:
			target = { pac.getPos().x + 2, pac.getPos().y };
			break;
		case 2:
			target = { pac.getPos().x, pac.getPos().y + 2 };
			break;
		case 3:
			target = { pac.getPos().x - 2, pac.getPos().y };
			break;
		}
		break;
	case 1:
		target = scatterPos;
	}
}

void BlueGhost::reset(bool)
{
	*this = BlueGhost();
	if (inBox)
		this->pos = { 13,15 };
}