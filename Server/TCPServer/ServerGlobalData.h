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
#define BOMB_EXPLOSION_COUNT 6000000

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
	Point bombPoint;	//��ġ
	int bombCountdown;		//Ÿ�̸�
	int bombExplosionLength;	//�Ҳ� ����
	int playerID;
	bool up = true;
	bool down = true;
	bool right = true;
	bool left = true;
	BombData(int px, int py, int count, int length, int id) { bombPoint.X = px; bombPoint.Y = py; bombCountdown = count; bombExplosionLength = length; playerID = id; }
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
SOCKET					playerSocket;
	KeyInput				key;
	int 					bombCount;				// ��ź ����
	Point 					position;				// �÷��̾� ��ġ
	bool					isAlive;				// ���� ����
	int						playerBombLength;		//��ź �ұ� ����
	std::vector<BombData>	playerBomb;				//�÷��̾� ��ź
	PlayerColor				playerColor;
};

struct MapData
{
	Item 	item; // �������� �ִ���
	bool	isRock; //�����ִ� ��
	bool 	isBomb; //��ź���ִ���
	bool	isBombFrame;	//��ź �ұ��� �ִ���
	PlayerColor playerColor;
};