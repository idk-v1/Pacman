#pragma once
#include "Ghost.h"
class BlueGhost : public Ghost
{
public:
	BlueGhost();

	void setTarget(Ghost*, Pacman&);

	void reset(bool);
};
