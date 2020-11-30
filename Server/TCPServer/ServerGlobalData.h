#pragma once
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Protocol.h"


#define MAX_PLAYER 3
#define MAP_SIZE 30


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
	char 		speed; //�÷��̾� �ӵ�
	char 		power; // ��ź ����
	Point 		position; // �÷��̾� ��ġ
	bool		isAlive; // ���� ����
	PlayerColor playerColor;
};

struct MapData
{
	Item 	item; // �������� �ִ���
	bool	isRock; //�����ִ� ��
	bool 	isBomb; //��ź���ִ���
	PlayerColor playerColor;
};