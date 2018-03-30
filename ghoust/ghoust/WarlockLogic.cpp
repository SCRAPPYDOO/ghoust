#include "stdafx.h"
#include "WarlockLogic.h"

WarlockLogic::WarlockLogic(PlayerObject * player) : Logic(player)
{
	classBuffList = { 
		SpellType::DEMON_SKIN
	};
}


WarlockLogic::~WarlockLogic()
{
}

void WarlockLogic::runLogic()
{
	buff();
}