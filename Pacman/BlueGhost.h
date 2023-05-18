#pragma once
#include "Ghost.h"
class BlueGhost : public Ghost
{
public:
	BlueGhost(sf::Texture&);

	void setTarget(Ghost*, Pacman&);

	void reset(sf::Texture&, bool);
};