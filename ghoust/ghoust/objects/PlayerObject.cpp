#include "stdafx.h"

#include "PlayerObject.h"
#include "ClassType.h"

boolean PlayerObject::isManaUser()
{
	int classType = this->getClass();

	switch (classType) {
		case WARRIOR:
		case ROGUE:
			return false;
		default: 
			return true;
	}
}
