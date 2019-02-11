#pragma once

#include "CreatureObject.h"

class NpcObject : public CreatureObject
{
	public:
		NpcObject(unsigned int baseAddress);
		~NpcObject();
};

