#pragma once
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Protocol.h"


#define MAX_PLAYER 3
#define MAP_SIZE 30
#define BOMB_EXPLOSION_COUNT 3000000

struct KeyInput //Ű �Է� on off
{
	bool key_Up;
	bool key_Down;
	bool key_Left;
	bool key_Right;
	bool key_Space;
};

struct Point
{
	int X;
	int Y;
};

struct BombData		//��ź Ÿ�̸� �� ��ź ��ġ�� �����
{
	Point bombPoint;
	int bombCount;
	int prevBombCount;
	int bombExplosionLength;
};

enum Item
{
	EMPTY,
	BALLON, //��ź ���� ����
	SHOES, //�÷��̾� �̵� �ӵ� ����
	POTION, //��ź ���� ����
};

enum PlayerColor
{
	RED,
	GREEN,
	BLUE,
	PLAYEREMPTY,
};

struct PlayerStatus  //�÷��̾��� ����, ���ٱ�, �̵��ӵ�, ��ġ, ���¸� ����
{
	SOCKET		playerSocket;
	KeyInput	key;
	char 		power; // ��ź ����
	Point 		position; // �÷��̾� ��ġ
	bool		isAlive; // ���� ����
	int			playerBombLength;	//��ź �ұ� ����
	PlayerColor playerColor;
};

struct MapData
{
	Item 	item; // �������� �ִ���
	bool	isRock; //�����ִ� ��
	bool 	isBomb; //��ź���ִ���
	bool	isBombFrame;	//��ź �ұ��� �ִ���
	PlayerColor playerColor;
};