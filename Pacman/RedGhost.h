#pragma once
#include "Ghost.h"
class RedGhost : public Ghost
{
public:
	RedGhost();

	void setTarget(std::vector<Ghost*>&, Pacman&);

	void reset();
};

