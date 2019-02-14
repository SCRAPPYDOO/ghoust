#pragma once

#include "Logic.h"
#include "WarlockSpellDefinition.h"

class WarlockLogic : public Logic
{
	public:
		WarlockLogic();
		~WarlockLogic();

	protected:
		bool checkIfCanCastSpell(Spell * spell);
		list<SpellId> getBuffList();
		SpellId selectSpell(CreatureObject* target);
		SpellId getSpellWithRank(WarlockSpellType spellType);
};

