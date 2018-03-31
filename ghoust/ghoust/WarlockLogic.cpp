#include "stdafx.h"
#include "WarlockLogic.h"

WarlockLogic::WarlockLogic(PlayerObject * player) : Logic(player)
{
	classBuffList = { 
		SpellType::WARLOCK_DEMON_SKIN_RANK_1,
	};
}


WarlockLogic::~WarlockLogic()
{
}

void WarlockLogic::runLogic()
{
	buff();
}