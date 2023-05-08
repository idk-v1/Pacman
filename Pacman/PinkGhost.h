#pragma once
#include "Ghost.h"

class PinkGhost : public Ghost
{
public:
	PinkGhost(sf::Texture&);

	void setTarget(Ghost*, Pacman&);

	void reset(sf::Texture&, bool);
};

