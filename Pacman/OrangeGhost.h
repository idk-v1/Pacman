#pragma once
#include "Ghost.h"
class OrangeGhost : public Ghost
{
public:
	OrangeGhost();

	void setTarget(Ghost*, Pacman&);

	void reset(bool);
};

