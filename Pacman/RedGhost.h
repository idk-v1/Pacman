#pragma once
#include "Ghost.h"
class RedGhost : public Ghost
{
public:
	RedGhost(sf::Texture&);

	void setTarget(Ghost*, Pacman&);

	void reset(sf::Texture&, bool);
};

