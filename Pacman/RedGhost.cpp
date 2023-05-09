#include "RedGhost.h"

RedGhost::RedGhost(sf::Texture &tex)
{
	texture = tex;
	rect.setTexture(&texture);
	texXOff = 0;
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

void RedGhost::reset(sf::Texture &tex, bool inBox)
{
	*this = RedGhost(tex);
	texture = tex;
	rect.setTexture(&texture);
	restart = 45 * 2;
	if (inBox)
		this->pos = { 13,15 };
}