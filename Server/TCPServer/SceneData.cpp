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
			if (m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y - 1].isRock == false)
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
			if (m_mapData[m_playerStatus[i].position.X - 1][m_playerStatus[i].position.Y].isRock == false)
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
				if (m_playerStatus[i].playerBomb.empty())		//제일 처음 폭탄 둘때
				{
					m_playerStatus[i].playerBomb.emplace_back(m_playerStatus[i].position.X, m_playerStatus[i].position.Y, BOMB_EXPLOSION_COUNT, m_playerStatus[i].playerBombLength);
					m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y].isBomb = true;
				}
				else
				{
					for (int j = 0; j < m_playerStatus[i].bombCount; j++)
					{
						if (m_playerStatus[i].playerBomb[j].bombCountdown <= 0)
						{
							m_playerStatus[i].playerBomb[j].bombPoint = { m_playerStatus[i].position.X, m_playerStatus[i].position.Y };
							m_playerStatus[i].playerBomb[j].bombCountdown = BOMB_EXPLOSION_COUNT;
							m_playerStatus[i].playerBomb[j].bombExplosionLength = m_playerStatus[i].playerBombLength;
							m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y].isBomb = true;
							break;
						}
						if ((j == m_playerStatus[i].playerBomb.size() - 1) && (m_playerStatus[i].bombCount > m_playerStatus[i].playerBomb.size()))
						{
							m_playerStatus[i].playerBomb.emplace_back(m_playerStatus[i].position.X, m_playerStatus[i].position.Y, BOMB_EXPLOSION_COUNT, m_playerStatus[i].playerBombLength);
							m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y].isBomb = true;
						}
					}
				}

			}
		}
		m_mapData[m_playerStatus[i].position.X][m_playerStatus[i].position.Y].playerColor = PlayerColor(i);


		if (!m_playerStatus[i].playerBomb.empty())
		{
			for (int k = 0; k < m_playerStatus[i].playerBomb.size(); k++)		//플레이어 길이로 처리하기
			{
				m_playerStatus[i].playerBomb[k].bombCountdown--;
				
				if (m_playerStatus[i].playerBomb[k].bombCountdown <= 0)
				{
					for (int l = 1; l < m_playerStatus[i].playerBombLength + 1; l++)
					{
						if (!m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X - l][m_playerStatus[i].playerBomb[k].bombPoint.Y].isRock && !(m_playerStatus[i].playerBomb[k].bombPoint.X - l < 0))
						{
							m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X - l][m_playerStatus[i].playerBomb[k].bombPoint.Y].isBombFrame = true;
						}
						if (!m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X + l][m_playerStatus[i].playerBomb[k].bombPoint.Y].isRock && !(m_playerStatus[i].playerBomb[k].bombPoint.X + l > MAP_SIZE))
						{
							m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X + l][m_playerStatus[i].playerBomb[k].bombPoint.Y].isBombFrame = true;
						}
						if (!m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X][m_playerStatus[i].playerBomb[k].bombPoint.Y - l].isRock && !(m_playerStatus[i].playerBomb[k].bombPoint.Y - l < 0))
						{
							m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X][m_playerStatus[i].playerBomb[k].bombPoint.Y - l].isBombFrame = true;
						}
						if (!m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X][m_playerStatus[i].playerBomb[k].bombPoint.Y + l].isRock && !(m_playerStatus[i].playerBomb[k].bombPoint.Y + l > MAP_SIZE))
						{
							m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X][m_playerStatus[i].playerBomb[k].bombPoint.Y + l].isBombFrame = true;
						}

						m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X][m_playerStatus[i].playerBomb[k].bombPoint.Y].isBombFrame = true;//폭탄이 있던 곳
						m_mapData[m_playerStatus[i].playerBomb[k].bombPoint.X][m_playerStatus[i].playerBomb[k].bombPoint.Y].isBomb = false;
					}
				}
			}
		}
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
	m_playerStatus[m_nPlayer].bombCount = 3;
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
