#pragma once

#define MAP_SIZE 30

#define GSE_GRAVITY 9.8f

#define GSE_WINDOW_WIDTH 700
#define GSE_WINDOW_HEIGHT 700

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

struct MapData
{
	Item 	item; // �������� �ִ���
	bool	isRock; //�����ִ� ��
	bool 	isBomb; //��ź���ִ���
	bool	isBombFrame;	//��ź �ұ��� �ִ���
	PlayerColor playerColor;
};

struct KeyInput //Ű �Է� on off
{
	bool key_UP;
	bool key_Down;
	bool key_Left;
	bool key_Right;
	bool key_Space;
};


////////////////////
enum Winner
{
	Winner_RED,
	Winner_GREEN,
	Winner_BLUE,
	Winner_DRAW,
};

struct FinishGame
{
	bool			FinishGame;
	Winner			Winner;
};