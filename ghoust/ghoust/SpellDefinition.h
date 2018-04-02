#pragma once

#include "Utils.h"

#include <map>

using namespace std;

enum SpellId {
	/*
		WARLOCK
	*/
	WARLOCK_DEMON_SKIN_RANK_1 = 687,
	WARLOCK_DEMON_SKIN_RANK_2 = 696,
	WARLOCK_SHADOW_BOLT = 686,

};

enum WarlockSpellTypeBinding {

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

	SpellId spellId;
	int castTime = 0;
	int duration = 0;
	int manaCost = 0;
	int actionBind = 0;
};

static map<SpellId, Spell*> spellList = {
	{ WARLOCK_DEMON_SKIN_RANK_1 , new Spell(WARLOCK_DEMON_SKIN_RANK_1, SECOND * 2, MINUTE * 30, 50, WarlockActionType::CAST_DEMON_SKIN) },
	{ WARLOCK_DEMON_SKIN_RANK_2 , new Spell(WARLOCK_DEMON_SKIN_RANK_2, SECOND * 2, MINUTE * 30, 120, WarlockActionType::CAST_DEMON_SKIN) },
	{ WARLOCK_SHADOW_BOLT , new Spell(WARLOCK_SHADOW_BOLT, SECOND * 2, 25, WarlockActionType::CAST_SHADOW_BOLT) },
};

static int getSpellManaCost(SpellId spellId) {
	return spellList[spellId]->manaCost;
}

static Spell* getSpellById(SpellId spellId) {
	return spellList[spellId];
}