#pragma once

#include "CreatureObject.h"

class PlayerObject : public CreatureObject
{
	public:
		PlayerObject(unsigned int baseAddress) : CreatureObject(baseAddress) {}
		~PlayerObject() {}
};

