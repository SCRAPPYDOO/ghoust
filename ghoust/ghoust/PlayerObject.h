#pragma once

#include "WowObject.h"

class PlayerObject : public WowObject
{
	public:
		PlayerObject(unsigned int baseAddress);
		~PlayerObject();
};

