#pragma once

#include "CreatureObject.h"

class PlayerObject : public CreatureObject
{
	public:
		PlayerObject(int baseAddress) : CreatureObject(baseAddress) {}
		~PlayerObject() {}

		boolean isManaUser();
};

