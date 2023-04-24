#pragma once
#include "Ghost.h"
class OrangeGhost : public Ghost
{
public:
	OrangeGhost();

	void setTarget(std::vector<Ghost*>&, Pacman&);

	void reset(bool);
};

