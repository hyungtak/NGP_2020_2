#pragma once

#include "ServerGlobalData.h"

#define SERVERPORT 9000
#define BUFSIZE    512

// Server to Client
#define S2C_PLAYER_POS			1
#define S2C_BOMB				2


struct S2C_PACKET_POS
{
	int size;
	int type;
	UCHAR id;
	float x, y;
};

struct S2C_PACKET_BOMB
{
	int size;
	int type;
	float x, y;
};


//////////////////////////////////


// Clinet to Server
#define C2S_KEY_PRESS_UP		1
#define C2S_KEY_PRESS_DOWN		2
#define C2S_KEY_PRESS_LEFT		3
#define C2S_KEY_PRESS_RIGHT		4
#define C2S_KEY_PRESS_SPACE		5


struct C2S_PACKET_KEYUP
{
	int size;
	int type;
};

struct C2S_PACKET_KEYDOWN
{
	int size;
	int type;
};

struct C2S_PACKET_KEYLEFT
{
	int size;
	int type;
};

struct C2S_PACKET_KEYRIGHT
{
	int size;
	int type;
};

struct C2S_PACKET_KEYSPACE
{
	int size;
	int type;
};

