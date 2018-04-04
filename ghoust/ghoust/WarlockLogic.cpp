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

SpellId WarlockLogic::selectSpell(CreatureObject* target) {
    /*
        Check for immolate
     */

	SpellId spell = getSpellWithRank(WarlockSpellType::WARLOCK_IMMOLATE);
	if (spell != NULL && !target->hasDebuff(spell)) {
		return spell;
	}

    /*
        Check for corruption
     */
    //if(!target->hasBuff()) {
        
    //}

	spell = getSpellWithRank(WarlockSpellType::WARLOCK_SHADOW_BOLT);
	return spell;
}

SpellId WarlockLogic::getSpellWithRank(WarlockSpellType spellType) {
	return WarlockSpellDefinition::getWarlockSpellIdByLevelAndSpellType(player->getCurrentLevel(), spellType);
}
