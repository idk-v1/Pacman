#include "BlueGhost.h"

BlueGhost::BlueGhost(sf::Texture &tex)
{
	texture = tex;
	rect.setTexture(&texture);
	texXOff = 3;
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
		}
		target.x -= red->getPos().x - pac.getPos().x;
		target.y -= red->getPos().y - pac.getPos().y;
		break;
	case 1:
		target = scatterPos;
	}
}

void BlueGhost::reset(sf::Texture &tex, bool)
{
	*this = BlueGhost(tex);
	texture = tex;
	rect.setTexture(&texture);
	restart = 45 * 2;
	if (inBox)
		this->pos = { 13,15 };
}