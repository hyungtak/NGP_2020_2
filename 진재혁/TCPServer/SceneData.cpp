#include "SceneData.h"

SceneData::SceneData()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			m_mapData[i][j].isBomb = false;
			m_mapData[i][j].isRock = false;
			m_mapData[i][j].item = EMPTY;
		}
	}
}

SceneData::~SceneData()
{

}

void SceneData::update()	
{
	for (int i = 0; i < MAX_PLAYER; i++) //변경해야함
	{
		if (m_playerStatus[i].key.key_Down)
		{
			m_playerStatus[i].position.Y -= 1;
			m_playerStatus[i].key.key_Down = false;
		}
		if (m_playerStatus[i].key.key_Up)
		{
			m_playerStatus[i].position.Y += 1;
			m_playerStatus[i].key.key_Up = false;
		}
		if (m_playerStatus[i].key.key_Left)
		{
			m_playerStatus[i].position.X -= 1;
			m_playerStatus[i].key.key_Left = false;
		}
		if (m_playerStatus[i].key.key_Right)
		{
			m_playerStatus[i].position.X += 1;
			m_playerStatus[i].key.key_Right = false;
		}
	}

	// 플레이어 좌표 출력 test용
	//for (int i = 0; i < MAX_PLAYER; i++)
	//{
	//	printf("m_playerStatus[%d].position = (%d, %d)\n", 
	//		i, m_playerStatus[i].position.X, m_playerStatus[i].position.Y);
	//}

}

void SceneData::setKeyInput(SOCKET socket, KeyInput key)
{
	for (int i = 0; i < MAX_PLAYER; i++) 
	{
		if (m_playerStatus[i].playerSocket == socket)
		{
			m_playerStatus[i].key = key;
			break;
		}
	}
}

void SceneData::setPlayer(SOCKET socket)
{
	m_playerStatus[m_nPlayer].playerSocket = socket;
	m_playerStatus[m_nPlayer].isAlive = true;
	m_playerStatus[m_nPlayer].position = { m_nPlayer * 10, m_nPlayer * 10 };
	m_playerStatus[m_nPlayer].power = 0;
	m_playerStatus[m_nPlayer].speed = 0;
	++m_nPlayer;
}

void SceneData::getPlayer(SOCKET socket, PlayerStatus* playerStatus)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (m_playerStatus[i].playerSocket == socket)
		{
			*playerStatus = m_playerStatus[i];
			break;
		}
	}
}
