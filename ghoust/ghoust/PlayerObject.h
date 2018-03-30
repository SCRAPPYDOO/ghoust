#pragma once

#include "CreatureObject.h"
#include "SpellType.h"

class PlayerObject : public Creatureobject
{
	public:
		PlayerObject(unsigned int baseAddress) : Creatureobject(baseAddress) {}
		~PlayerObject() {}
};

