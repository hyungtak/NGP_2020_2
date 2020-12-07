#pragma once
#include "ServerGlobalData.h"
#include <queue>

class SceneData
{
public:
	SceneData();
	~SceneData();

private:
	Player					m_players[MAX_PLAYER];
	int						m_nPlayer = 0;
	std::vector<BombData>	m_bombManger;
	MapData					m_mapData[MAP_SIZE][MAP_SIZE];
	FinishGame				finishgame;
	bool					startgame;

public:
	void Update();
	void SetKeyInput(SOCKET socket, KeyInput key);
	MapData GetMapData(int n, int m) { return m_mapData[n][m]; };
	void SetPlayer(SOCKET socket);
	FinishGame GetGameFinish() { return finishgame; };
	void StartGame() { startgame = 1; };
};

