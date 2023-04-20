#include "RedGhost.h"

RedGhost::RedGhost()
{
	color = sf::Color(0xFF0000FF);
	pos = { 13, 11 };
	target = { 13.5, 23 };
	scatterPos = { 28, 0 };
	mode = 0;
	dotReq = 0;
}

void RedGhost::setTarget(std::vector<Ghost*>& ghosts, Pacman& pac)
{
	target = pac.getPos();
}

void RedGhost::reset()
{
	*this = RedGhost();
}