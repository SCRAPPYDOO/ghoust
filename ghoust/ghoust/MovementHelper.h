#pragma once

#include "Position.h"

class MovementHelper
{
	public:
		static const float pointDegree;
		static float findDirection(Position* characterPosition, Position* targetPosition);
		static float findRange(Position* characterPosition, Position* targetPosition);
};

