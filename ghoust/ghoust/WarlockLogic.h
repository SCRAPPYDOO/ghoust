#pragma once

#include "Logic.h"

class WarlockLogic : public Logic
{
	public:
		WarlockLogic();
		~WarlockLogic();

		

	protected:
		bool checkIfCanCastSpell(Spell * spell);
		list<SpellId> getBuffList();
		SpellId selectSpell(CreatureObject* target);
};

