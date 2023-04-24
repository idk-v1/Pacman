#pragma once
#include "Ghost.h"

class PinkGhost : public Ghost
{
public:
	PinkGhost();

	void setTarget(Ghost*, Pacman&);

	void reset(bool);
};

