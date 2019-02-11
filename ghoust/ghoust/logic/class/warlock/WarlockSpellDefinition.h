#pragma once

#include "SpellDefinition.h"
#include "WarlockSpellType.h"
#include <map>

using namespace std;

class WarlockSpellDefinition {
	public:
		static SpellId getWarlockSpellIdByLevelAndSpellType(int level, WarlockSpellType spellType) {
			return warlockSpellByLevel[level][spellType];
		}

		static map<int, map<WarlockSpellType, SpellId>> warlockSpellByLevel;
};
