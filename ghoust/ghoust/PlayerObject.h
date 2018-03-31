#pragma once

#include "CreatureObject.h"

class PlayerObject : public Creatureobject
{
	public:
		PlayerObject(unsigned int baseAddress) : Creatureobject(baseAddress) {}
		~PlayerObject() {}
};

