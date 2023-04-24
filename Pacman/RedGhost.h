#pragma once
#include "Ghost.h"
class RedGhost : public Ghost
{
public:
	RedGhost();

	void setTarget(Ghost*, Pacman&);

	void reset(bool);
};

