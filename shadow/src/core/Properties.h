#pragma once

using namespace std;

enum BotType {
	FOLLOWER,
	BOT,
	SLAVE
};

class Properties {
	public:
		static BotType botType;

		static string getClassTypeName(int classType);

		static const int SPELL_CAST_TIME = 500;
};
