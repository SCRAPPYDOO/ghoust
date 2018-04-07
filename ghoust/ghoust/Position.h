#pragma once

struct Position {

	Position() {}
	Position(float posX, float posY) {
		this->posX = posX;
		this->posY = posY;
	}

	float posX;
	float posY;
	float posZ;
	float rotation;
};