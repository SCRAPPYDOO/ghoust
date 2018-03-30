#pragma once

#include "ClassType.h"

using namespace std;

class Properties {
	public:
		static ClassType playerClassType;
		static string getClassTypeName(ClassType classType);
		static string getPlayerClassTypeName();
};