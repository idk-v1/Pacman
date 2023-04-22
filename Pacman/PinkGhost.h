#pragma once
#include "Ghost.h"

class PinkGhost : public Ghost
{
public:
	PinkGhost();

	void setTarget(std::vector<Ghost*>&, Pacman&);

	void reset(bool);
};

