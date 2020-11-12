#pragma once

#define GSE_MAX_OBJECTS 1000

typedef struct GSEInputs
{
	bool ARROW_UP;
	bool ARROW_DOWN;
	bool ARROW_LEFT;
	bool ARROW_RIGHT;
	bool KEY_W;
	bool KEY_A;
	bool KEY_S;
	bool KEY_D;

};

typedef struct GSEUpdateParams
{
	float forceX;
	float forceY;
};