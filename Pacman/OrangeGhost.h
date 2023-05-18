#pragma once
#include "Ghost.h"
class OrangeGhost : public Ghost
{
public:
	OrangeGhost(sf::Texture&);

	void setTarget(Ghost*, Pacman&);

	void reset(sf::Texture&, bool);
};