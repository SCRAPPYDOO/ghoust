#pragma once

#include "ClassType.h"

using namespace std;

enum BotType {
	FOLLOWER,
	BOT
};

class Properties {
	public:
		static BotType botType;

		static string getClassTypeName(int classType);

		static const int SPELL_CAST_TIME = 500;
};