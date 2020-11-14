#pragma once
#include "ServerGlobalData.h"
class SceneData
{
public:
	SceneData();
	~SceneData();

private:
	PlayerStatus	m_playerStatus[MAX_PLAYER];
	MapData			m_mapData[MAP_SIZE][MAP_SIZE];
	char			m_nPlayer = 0;
public:
	void update();
	void setKeyInput(SOCKET socket, KeyInput key);
	void getMapData(MapData mapData[MAP_SIZE][MAP_SIZE]) { mapData = m_mapData; };
	void setPlayer(SOCKET socket);
	void getPlayer(SOCKET socket, PlayerStatus * playerStatus);
};

