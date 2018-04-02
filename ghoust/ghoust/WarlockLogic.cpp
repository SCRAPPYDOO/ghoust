#include "stdafx.h"
#include "WarlockLogic.h"

WarlockLogic::WarlockLogic()
{
}

WarlockLogic::~WarlockLogic()
{
}

bool WarlockLogic::checkIfCanCastSpell(Spell* spell) {
	return true;
}

list<SpellId> WarlockLogic::getBuffList() {
	list<SpellId> list;
	if (player->getCurrentLevel() > 9) {
		list = { SpellId::WARLOCK_DEMON_SKIN_RANK_2  };
	} else {
		list = { SpellId::WARLOCK_DEMON_SKIN_RANK_1  };
	}
	return list;
}

SpellId WarlockLogic::selectSpell(NpcObject* target) {
	return SpellId::WARLOCK_SHADOW_BOLT;
}