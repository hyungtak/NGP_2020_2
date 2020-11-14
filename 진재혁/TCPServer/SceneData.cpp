#include "SceneData.h"

SceneData::SceneData()
{
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
			m_playerStatus[i].position.y -= 1;
			m_playerStatus[i].key.key_Down = false;
		}
		if (m_playerStatus[i].key.key_UP)
		{
			m_playerStatus[i].position.y += 1;
			m_playerStatus[i].key.key_UP = false;
		}
		if (m_playerStatus[i].key.key_Left)
		{
			m_playerStatus[i].position.x -= 1;
			m_playerStatus[i].key.key_Left = false;
		}
		if (m_playerStatus[i].key.key_Right)
		{
			m_playerStatus[i].position.x += 1;
			m_playerStatus[i].key.key_Right = false;
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
