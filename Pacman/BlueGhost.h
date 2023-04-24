#pragma once
#include "Ghost.h"
class BlueGhost : public Ghost
{
public:
	BlueGhost();

	void setTarget(std::vector<Ghost*>&, Pacman&);

	void reset(bool);
};
