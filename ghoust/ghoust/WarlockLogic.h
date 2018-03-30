#pragma once

#include "Logic.h"

class WarlockLogic : public Logic
{
	public:
		WarlockLogic(PlayerObject * player);
		~WarlockLogic();

		void runLogic();
};

