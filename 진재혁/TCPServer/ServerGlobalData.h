#pragma once
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_PLAYER 3
#define MAP_SIZE 30


struct KeyInput //키 입력 on off
{
	bool key_Up;
	bool key_Down;
	bool key_Left;
	bool key_Right;
	bool key_Space;
};

struct Point
{
	short X;
	short Y;
};

enum Item
{
	EMPTY,
	BALLON, //폭탄 개수 증가
	SHOES, //플레이어 이동 속도 증가
	POTION, //폭탄 길이 증가
};

struct PlayerStatus  //플레이어의 소켓, 물줄기, 이동속도, 위치, 상태를 저장
{
	SOCKET		playerSocket;
	KeyInput	key;
	char 		speed; //플레이어 속도
	char 		power; // 폭탄 길이
	Point 		position; // 플레이어 위치
	bool		isAlive; // 생존 여부
};

struct MapData
{
	Item 	item; // 아이템이 있는지
	bool	isRock; //막혀있는 곳
	bool 	isBomb; //폭탄이있는지
};

