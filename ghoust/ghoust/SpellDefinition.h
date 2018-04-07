#pragma once

#include "Utils.h"
#include "ActionType.h"

#include <map>

using namespace std;

enum SpellId {
	/*
		WARLOCK
	*/
	WARLOCK_DEMON_SKIN_RANK_1 = 687,
	WARLOCK_DEMON_SKIN_RANK_2 = 696,

	WARLOCK_SHADOW_BOLT_1 = 686,
	WARLOCK_SHADOW_BOLT_2 = 695,
	WARLOCK_SHADOW_BOLT_3 = 705,

	WARLOCK_IMMOLATE_1 = 348,
	WARLOCK_IMMOLATE_2 = 707,
	WARLOCK_IMMOLATE_3 = 1094,
	WARLOCK_IMMOLATE_4 = 2941,
	WARLOCK_IMMOLATE_5 = 11665,
	WARLOCK_IMMOLATE_6 = 11667,
	WARLOCK_IMMOLATE_7 = 11668,
	WARLOCK_IMMOLATE_8 = 25309,

	WARLOCK_CORRUPTION_1 = 172,   // 1-13
	WARLOCK_CORRUPTION_2 = 6222,

	WARLOCK_CURSE_OF_AGONY_1 = 980,

	/*
		WARLOCK DOT ON TARGET DEFINITIONS
	*/
};

struct Spell {
	Spell(SpellId spellId, int duration, int manaCost, int actionBind) {
		this->spellId = spellId;
		this->duration = duration;
		this->manaCost = manaCost;
		this->actionBind = actionBind;
	}

	Spell(SpellId spellId, int castTime, int duration, int manaCost, int actionBind) {
		this->spellId = spellId;
		this->castTime = castTime;
		this->duration = duration;
		this->manaCost = manaCost;
		this->actionBind = actionBind;
	}

	Spell(SpellId spellId, int castTime, int duration, int manaCost, int actionBind, int range) {
		this->spellId = spellId;
		this->castTime = castTime;
		this->duration = duration;
		this->manaCost = manaCost;
		this->actionBind = actionBind;
		this->range = range;
	}

	SpellId spellId;
	int castTime = 0;
	int duration = 0;
	int manaCost = 0;
	int actionBind;
	int range = 0;
};

static map<SpellId, Spell*> spellList = {
	{ WARLOCK_DEMON_SKIN_RANK_1 , new Spell(WARLOCK_DEMON_SKIN_RANK_1, SECOND * 2, MINUTE * 30, 50, WarlockActionType::CAST_DEMON_SKIN) },
	{ WARLOCK_DEMON_SKIN_RANK_2 , new Spell(WARLOCK_DEMON_SKIN_RANK_2, SECOND * 2, MINUTE * 30, 120, WarlockActionType::CAST_DEMON_SKIN) },
	{ WARLOCK_SHADOW_BOLT_1 , new Spell(WARLOCK_SHADOW_BOLT_1, SECOND * 2, 0, 25, WarlockActionType::CAST_SHADOW_BOLT, 30) },
	{ WARLOCK_SHADOW_BOLT_2 , new Spell(WARLOCK_SHADOW_BOLT_2, SECOND * 2, 0, 40, WarlockActionType::CAST_SHADOW_BOLT, 30) },
	{ WARLOCK_SHADOW_BOLT_3 , new Spell(WARLOCK_SHADOW_BOLT_2, SECOND * 2, 0, 70, WarlockActionType::CAST_SHADOW_BOLT, 30) },
	{ WARLOCK_IMMOLATE_1 , new Spell(WARLOCK_IMMOLATE_1, SECOND * 2, 0, 25, WarlockActionType::CAST_IMMOLATE, 30) },
	{ WARLOCK_CORRUPTION_1, new Spell(WARLOCK_CORRUPTION_1, SECOND * 2, 0, 35, WarlockActionType::CAST_CORRUPTION, 30) },
	{ WARLOCK_CORRUPTION_2 , new Spell(WARLOCK_CORRUPTION_1, SECOND * 2, 0, 55, WarlockActionType::CAST_CORRUPTION, 30) },
	{ WARLOCK_CURSE_OF_AGONY_1 , new Spell(WARLOCK_CURSE_OF_AGONY_1, SECOND * 2, 0, 25, WarlockActionType::CAST_CURSE_OF_AGONY, 30)},
};


static int getSpellManaCost(SpellId spellId) {
	return spellList[spellId]->manaCost;
}

static Spell* getSpellById(SpellId spellId) {
	return spellList[spellId];
}
