#pragma once
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>

#define MAX_PLAYER 3
#define MAP_SIZE 30
#define BOMB_EXPLOSION_COUNT 6000000

#define SERVERPORT 9000
#define BUFSIZE    512

struct KeyInput //키 입력 on off
{
	bool key_Up;
	bool key_Down;
	bool key_Left;
	bool key_Right;
	bool key_Space;
	bool key_F5;
};

struct Point
{
	int X;
	int Y;
};

struct BombData		//폭탄 타이머 및 폭탄 위치값 저장용
{
	Point bombPoint;	//위치
	std::chrono::system_clock::time_point bombCountdown;		//타이머
	int bombExplosionLength;	//불꽃 길이
	int playerID;
	bool up = true;
	bool down = true;
	bool right = true;
	bool left = true;
	BombData(int px, int py, std::chrono::system_clock::time_point count, int length, int id) { bombPoint.X = px; bombPoint.Y = py; bombCountdown = count; bombExplosionLength = length; playerID = id; }
};

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

struct PlayerStatus  //플레이어의 소켓, 물줄기, 이동속도, 위치, 상태를 저장
{
SOCKET					playerSocket;
	KeyInput				key;
	int 					bombCount;				// 폭탄 개수
	Point 					position;				// 플레이어 위치
	bool					isAlive;				// 생존 여부
	int						playerBombLength;		//폭탄 불길 길이
	PlayerColor				playerColor;
	bool		isReady;	// 준비 여부
};

struct MapData
{
	Item 	item; // 아이템이 있는지
	bool	isRock; //막혀있는 곳
	bool 	isBomb; //폭탄이있는지
	bool	isBombFrame;	//폭탄 불길이 있는지
	PlayerColor playerColor;
};
