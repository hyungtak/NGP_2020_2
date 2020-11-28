#include "SceneData.h"

SceneData::SceneData()
{
	for (int i = 0; i < MAP_SIZE; i++)		//세로
	{
		for (int j = 0; j < MAP_SIZE; j++)	//가로
		{
			m_mapData[i][j].isBomb = false;
			if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1)
				m_mapData[i][j].isRock = true;
			else if (i % 3 == 2 && j % 3 == 2)
				m_mapData[i][j].isRock = true;
			else
				m_mapData[i][j].isRock = false;

			m_mapData[i][j].item = Item::EMPTY;
			m_mapData[i][j].playerColor = PlayerColor::PLAYEREMPTY;
		}
	}
}

SceneData::~SceneData()
{

}

void SceneData::update()	
{
	int j = 0;

	for (int i = 0; i < m_nPlayer; i++) //변경해야함
	{
		m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y].playerColor = PlayerColor::PLAYEREMPTY;

		if (m_playerStatus[i].key.key_Down)
		{
			if(m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y-1].isRock == false)
				m_playerStatus[i].position.Y -= 1;
			m_playerStatus[i].key.key_Down = false;
		}
		if (m_playerStatus[i].key.key_Up)
		{
			if (m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y + 1].isRock == false)
				m_playerStatus[i].position.Y += 1;
			m_playerStatus[i].key.key_Up = false;
		}
		if (m_playerStatus[i].key.key_Left)
		{
			if (m_mapData[m_playerStatus[i].position.X-1][m_playerStatus[i].position.Y].isRock == false)
				m_playerStatus[i].position.X -= 1;
			m_playerStatus[i].key.key_Left = false;
		}
		if (m_playerStatus[i].key.key_Right)
		{
			if (m_mapData[m_playerStatus[i].position.X + 1][m_playerStatus[i].position.Y].isRock == false)
				m_playerStatus[i].position.X += 1;
			m_playerStatus[i].key.key_Right = false;
		}
		if (m_playerStatus[i].key.key_Space)				//폭탄 처리
		{
			if (m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y].isBomb == false) 
			{
				if(m_qBomb.empty())
					m_qBomb.push({ { m_playerStatus[i].position.X,m_playerStatus[i].position.Y }, BOMB_EXPLOSION_COUNT, 0, m_playerStatus[i].playerBombLength });
				else
					m_qBomb.push({ { m_playerStatus[i].position.X,m_playerStatus[i].position.Y }, BOMB_EXPLOSION_COUNT, BOMB_EXPLOSION_COUNT - m_qBomb.front().bombCount, m_playerStatus[i].playerBombLength });

				m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y].isBomb = true;
			}
		}
		m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y].playerColor = PlayerColor(i);
	}

	// 플레이어 좌표 출력 test용
	//for (int i = 0; i < MAX_PLAYER; i++)
	//{
	//	printf("m_playerStatus[%d].position = (%d, %d)\n", 
	//		i, m_playerStatus[i].position.X, m_playerStatus[i].position.Y);
	//}
	
	if (!m_qBomb.empty()) {
		if (m_qBomb.front().bombCount == m_qBomb.front().prevBombCount)			//폭탄이 놓여지게 된 순간부터 카운트가 작동하도록 수정해야됨
		{
			for (int i = 1; i < m_qBomb.front().bombExplosionLength + 1; i++)		//플레이어 길이로 처리하기
			{
				if (!m_mapData[m_qBomb.front().bombPoint.X - i][m_qBomb.front().bombPoint.Y].isRock)
				{
					m_mapData[m_qBomb.front().bombPoint.X - i][m_qBomb.front().bombPoint.Y].isBombFrame = true;
				}
				if (!m_mapData[m_qBomb.front().bombPoint.X + i][m_qBomb.front().bombPoint.Y].isRock)
				{
					m_mapData[m_qBomb.front().bombPoint.X + i][m_qBomb.front().bombPoint.Y].isBombFrame = true;
				}
				if (!m_mapData[m_qBomb.front().bombPoint.X][m_qBomb.front().bombPoint.Y - i].isRock)
				{
					m_mapData[m_qBomb.front().bombPoint.X][m_qBomb.front().bombPoint.Y - i].isBombFrame = true;
				}
				if (!m_mapData[m_qBomb.front().bombPoint.X][m_qBomb.front().bombPoint.Y + i].isRock)
				{
					m_mapData[m_qBomb.front().bombPoint.X][m_qBomb.front().bombPoint.Y + i].isBombFrame = true;
				}
			}
			m_mapData[m_qBomb.front().bombPoint.X][m_qBomb.front().bombPoint.Y].isBombFrame = true;
			m_mapData[m_qBomb.front().bombPoint.X][m_qBomb.front().bombPoint.Y].isBomb = false;
			m_qBomb.pop();
		}
		if (!m_qBomb.empty())
			m_qBomb.front().bombCount--;
	}

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
	m_playerStatus[m_nPlayer].position = { (m_nPlayer * 5) + 1, (m_nPlayer * 5)+1 };
	m_playerStatus[m_nPlayer].power = 0;
	m_playerStatus[m_nPlayer].playerBombLength = 1;
	m_playerStatus[m_nPlayer].playerColor = PlayerColor(m_nPlayer);
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
