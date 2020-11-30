#pragma once

#define MAP_SIZE 30

#define GSE_GRAVITY 9.8f

#define GSE_WINDOW_WIDTH 800
#define GSE_WINDOW_HEIGHT 600

enum Item
{
	EMPTY,
	BALLON, //폭탄 개수 증가
	SHOES, //플레이어 이동 속도 증가
	POTION, //폭탄 길이 증가
};

enum PlayerColor
{
	RED,
	GREEN,
	BLUE,
	PLAYEREMPTY,
};

struct MapData
{
	Item 	item; // 아이템이 있는지
	bool	isRock; //막혀있는 곳
	bool 	isBomb; //폭탄이있는지
	PlayerColor playerColor;
};

struct KeyInput //키 입력 on off
{
	bool key_UP;
	bool key_Down;
	bool key_Left;
	bool key_Right;
	bool key_Space;
	bool key_F5;
};
