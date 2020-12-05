#pragma once
#include "ServerGlobalData.h"
class SceneData
{
public:
	SceneData();
	~SceneData();

private:
<<<<<<< Updated upstream
	PlayerStatus	m_playerStatus[MAX_PLAYER];
	int				m_nPlayer = 0;


public:
	MapData			m_mapData[MAP_SIZE][MAP_SIZE];
	void update();
	void setKeyInput(SOCKET socket, KeyInput key);
	MapData getMapData(int n, int m) { return m_mapData[n][m]; };
	void setPlayer(SOCKET socket);
	void getPlayer(SOCKET socket, PlayerStatus* playerStatus);

	int	readyPlayer = 0;
=======
	Player					m_players[MAX_PLAYER];
	int						m_nPlayer = 0;
	std::vector<BombData>	m_bombManger;
	MapData					m_mapData[MAP_SIZE][MAP_SIZE];


public:
	bool	isAllReady = 0;


	void Update();
	void SetKeyInput(SOCKET socket, KeyInput key);
	MapData GetMapData(int n, int m) { return m_mapData[n][m]; };
	void SetPlayer(SOCKET socket);
	void PressReady(int x);
>>>>>>> Stashed changes
};

