#pragma once

#include "Logic.h"

class WarlockLogic : public Logic
{
	public:
		WarlockLogic(PlayerObject * player);
		~WarlockLogic();

		

	protected:
		bool checkIfCanCastSpell(Spell * spell);
		list<SpellId> getBuffList();
};

