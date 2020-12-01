#pragma once
#include "ServerGlobalData.h"
#include <queue>

class SceneData
{
public:
	SceneData();
	~SceneData();

private:
	PlayerStatus	m_playerStatus[MAX_PLAYER];
int				m_nPlayer = 0;
	unsigned int	m_nBombCheckCount = 0;
	std::vector<BombData>	BombManger;
public:
	MapData			m_mapData[MAP_SIZE][MAP_SIZE];
	void update();
	void setKeyInput(SOCKET socket, KeyInput key);
	MapData getMapData(int n, int m) { return m_mapData[n][m]; };
	void setPlayer(SOCKET socket);
	void getPlayer(SOCKET socket, PlayerStatus* playerStatus);

	int	readyPlayer = 0;
};

