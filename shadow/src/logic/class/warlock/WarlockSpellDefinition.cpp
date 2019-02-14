#include "stdafx.h"

#include "WarlockSpellDefinition.h"
#include <map>

using namespace std;

map<int, map<WarlockSpellType, SpellId>> WarlockSpellDefinition::warlockSpellByLevel = {
	{
		1 ,
        {
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_1 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
        }
	},

	{
		2 ,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_1 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
        }

	},

	{
		3,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_1 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
        }

	},

	{
		4,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_1 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
        }

	},

	{
		5,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_1 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
        }
	},

	{
		6,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_2 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
        }
	},

	{
		7,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_2 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
        }
	},

	{
		8,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_2 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
        }

	},

	{
		9,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_2 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
        }
	},

	{
		10,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 }, //2
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_2 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 }, //2
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
            { WARLOCK_CURSE_OF_AGONY, WARLOCK_CURSE_OF_AGONY_1 },
        }
	},

	{
		11,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_1 }, //2
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_2 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_1 },//2
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
            { WARLOCK_CURSE_OF_AGONY, WARLOCK_CURSE_OF_AGONY_1 },
        }
	},

	{
		12,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_2 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_3 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_2 },
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
            { WARLOCK_CURSE_OF_AGONY, WARLOCK_CURSE_OF_AGONY_1 },
        }
	},

	{
		13,
        {
            { WARLOCK_IMMOLATE, WARLOCK_IMMOLATE_2 },
            { WARLOCK_SHADOW_BOLT, WARLOCK_SHADOW_BOLT_3 },
            { WARLOCK_DEMON_SKIN, WARLOCK_DEMON_SKIN_RANK_2 },
            { WARLOCK_CORRUPTION, WARLOCK_CORRUPTION_1 },
        }
	},

    {
        14,
        {
        },
    },

    {
        15,
        {
        },
    },

    {
        16,
        {
        },
    },

    {
        17,
        {
        },
    },
    {
        18,
        {
        },
    },
    {
        19,
        {
        },
    },
    {
        20,
        {
        },
    },
};
