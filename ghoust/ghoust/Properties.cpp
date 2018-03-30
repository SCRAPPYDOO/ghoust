#include "stdafx.h"
#include "Properties.h"

ClassType Properties::playerClassType;

string Properties::getClassTypeName(ClassType classType)
{
	string className = "UKNOWN CLASS";
	switch (classType) {
		case WARRIOR: className = "WARRIOR"; break;
		case PALADIN: className = "PALADIN"; break;
		case HUNTER: className = "HUNTER"; break;
		case ROGUE: className = "ROGUE"; break;
		case PRIEST: className = "PRIEST"; break;
		case SHAMAN: className = "SHAMAN"; break;
		case MAGE: className = "MAGE"; break;
		case WARLOCK: className = "WARLOCK"; break;
		case DRUID: className = "DRUID"; break;
	}

	return className;
}

string Properties::getPlayerClassTypeName()
{
	return Properties::getClassTypeName(Properties::playerClassType);
}
