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

	/*
		DEMON SKIN
	*/
	SpellId buff = getSpellWithRank(WarlockSpellType::WARLOCK_DEMON_SKIN);
	if (buff != NULL) {
		list.push_back(buff);
	}

	//ToDO add all demon armors  to 1 buff typew
	
	return list;
}

SpellId WarlockLogic::selectSpell(CreatureObject* target) {
	/*
	Check for corruption
	*/
	SpellId spell = getSpellWithRank(WarlockSpellType::WARLOCK_CORRUPTION);
	if (spell != NULL && !target->hasDebuff(spell)) {
		return spell;
	}
	/*
	Check for curse of agony
	*/
	spell = getSpellWithRank(WarlockSpellType::WARLOCK_CURSE_OF_AGONY);
	if (spell != NULL && !target->hasDebuff(spell)) {
		return spell;
	}
	/*
	Check for immolate
	*/
	//spell = NULL; // getSpellWithRank(WarlockSpellType::WARLOCK_IMMOLATE);
	//if (spell != NULL && !target->hasDebuff(spell)) {
	//	return spell;
	//}

	spell = getSpellWithRank(WarlockSpellType::WARLOCK_SHADOW_BOLT);
	return spell;
}

SpellId WarlockLogic::getSpellWithRank(WarlockSpellType spellType) {
	return WarlockSpellDefinition::getWarlockSpellIdByLevelAndSpellType(player->getCurrentLevel(), spellType);
}
