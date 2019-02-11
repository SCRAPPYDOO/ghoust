#pragma once

#include "WowObject.h"

float findDirection(Position* characterPosition, Position* targetPosition) {
	float direction = 0.0f;

	int mainDirection = 0;

	float x1 = characterPosition->posX;
	float y1 = characterPosition->posY;

	float x2 = targetPosition->posX;
	float y2 = targetPosition->posY;

	char xMod = '=';
	char yMod = '=';

	float x3 = 0;
	float y3 = 0;

	if (x1 > x2) {
		xMod = '-';
		x3 = x1 - x2;
	}
	else if (x1 < x2) {
		xMod = '+';
		x3 = x2 - x1;
	}

	if (y1 > y2) {
		yMod = '-';
		y3 = y1 - y2;
	}
	else if (y1 < y2) {
		yMod = '+';
		y3 = y2 - y1;
	}

	float mod3 = 0.0f;

	if (xMod == '+' && yMod == '+' && x3 > y3) {
		mainDirection = 1;
		mod3 = y3 / x3 * pointDegree;
		direction = 0.0f + mod3;
	}
	else if (xMod == '+' && yMod == '+' && x3 < y3) {
		mainDirection = 2;
		mod3 = x3 / y3 * pointDegree;
		direction = 2 * pointDegree - mod3;
	}
	else if (xMod == '+' && yMod == '+' && x3 == y3) {
		mainDirection = 1122;
		direction = pointDegree;
	}

	else if (xMod == '-' && yMod == '+' && x3 > y3) {
		mainDirection = 4;
		mod3 = y3 / x3 * pointDegree;
		direction = 4 * pointDegree - mod3;
	}
	else if (xMod == '-' && yMod == '+' && x3 < y3) {
		mainDirection = 3;
		mod3 = x3 / y3 * pointDegree;
		direction = 2 * pointDegree + mod3;
	}
	else if (xMod == '-' && yMod == '+' && x3 == y3) {
		mainDirection = 3344;
		direction = 3 * pointDegree;
	}

	else if (xMod == '-' && yMod == '-' && x3 > y3) {
		mainDirection = 5;
		mod3 = y3 / x3 * pointDegree;
		direction = 4 * pointDegree + mod3;
	}
	else if (xMod == '-' && yMod == '-' && x3 < y3) {
		mainDirection = 6;
		mod3 = x3 / y3 * pointDegree;
		direction = 6 * pointDegree - mod3;
	}
	else if (xMod == '-' && yMod == '-' && x3 == y3) {
		mainDirection = 5566;
		direction = 5 * pointDegree;
	}

	else if (xMod == '+' && yMod == '-' && x3 > y3) {
		mainDirection = 8;
		mod3 = y3 / x3 * pointDegree;
		direction = 8 * pointDegree - mod3;
	}
	else if (xMod == '+' && yMod == '-' && x3 < y3) {
		mainDirection = 7;
		mod3 = x3 / y3 * pointDegree;
		direction = 6 * pointDegree + mod3;
	}
	else if (xMod == '+' && yMod == '-' && x3 == y3) {
		mainDirection = 7788;
		direction = 7 * pointDegree;
	}

	else if (xMod == '=' && yMod == '+') {
		mainDirection = 1111;
		direction = 2 * pointDegree;
	}
	else if (xMod == '=' && yMod == '-') {
		mainDirection = 3333;
		direction = 6 * pointDegree;
	}
	else if (xMod == '+' && yMod == '=') {
		mainDirection = 2222;
		direction = 0.0f;
	}
	else if (xMod == '-' && yMod == '=') {
		mainDirection = 4444;
		direction = 4 * pointDegree;
	}

	return direction;
}