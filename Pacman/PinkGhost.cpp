#include "PinkGhost.h"

PinkGhost::PinkGhost(sf::Texture &tex)
{
	texture = tex;
	rect.setTexture(&texture);
	texXOff = 1;
	pos = { 13, 15 };
	target = { 13, 11 };
	scatterPos = { 0, 0 };
	mode = 1;
	dotReq = 0;
}

void PinkGhost::setTarget(Ghost* red, Pacman& pac)
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

	if (dead)
	{
		target = { 13.5, 12 };
	}
}

void PinkGhost::reset(sf::Texture &tex, bool)
{
	*this = PinkGhost(tex);
	texture = tex;
	rect.setTexture(&texture);
	restart = 45 * 2;
	if (inBox)
		this->pos = { 13,15 };
}