#pragma once
#include "ServerGlobalData.h"
class SceneData
{
public:
	SceneData();
	~SceneData();

private:
	PlayerStatus	m_playerStatus[MAX_PLAYER];
	char			m_nPlayer = 0;

public:
	MapData			m_mapData[MAP_SIZE][MAP_SIZE];
	void update();
	void setKeyInput(SOCKET socket, KeyInput key);
	MapData getMapData(int n, int m) { return m_mapData[n][m]; };
	void setPlayer(SOCKET socket);
	void getPlayer(SOCKET socket, PlayerStatus* playerStatus);
};

