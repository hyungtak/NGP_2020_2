#include "stdafx.h"
#include "GSEGame.h"

GSEGame::GSEGame()
{
	//Renderer 생성
	m_renderer = new Renderer(GSE_WINDOW_WIDTH, GSE_WINDOW_HEIGHT);

	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			m_pMapdata[i][j].isBomb = false;
			m_pMapdata[i][j].isRock = false;
			m_pMapdata[i][j].item = Item::EMPTY;
			m_pMapdata[i][j].playerColor = PlayerColor::PLAYEREMPTY;
		}
	}
}

GSEGame::~GSEGame()
{
	//Renderer 삭제
}

void GSEGame::RendererScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	//m_renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);

	//Draw all objects
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (m_pMapdata[i][j].isBomb == true)		//폭탄이 있을 경우
			{
				m_renderer->DrawSolidRect(i * 4, i * 4, 0, 4, 0.4f, 0.4f, 0.4f,1.0f);
			}
			if (m_pMapdata[i][j].isRock == true)		//벽이 있을 경우
			{
				m_renderer->DrawSolidRect(i * 4, i * 4, 0, 4, 0.8f, 0.8f, 0.8f, 1.0f);
			}
			if (m_pMapdata[i][j].item != Item::EMPTY)	//아이템이 있을 경우
			{
				switch (m_pMapdata[i][j].item)
				{
				case Item::BALLON:
					m_renderer->DrawSolidRect(i * 4, i * 4, 0, 4, 0.8f, 0.8f, 0.8f, 1.0f);
					break;
				case Item::POTION:
					m_renderer->DrawSolidRect(i * 4, i * 4, 0, 4, 0.8f, 0.8f, 0.8f, 1.0f);
					break;
				case Item::SHOES:
					m_renderer->DrawSolidRect(i * 4, i * 4, 0, 4, 0.8f, 0.8f, 0.8f, 1.0f);
					break;
				}
			}
			if (m_pMapdata[i][j].playerColor != PlayerColor::PLAYEREMPTY)
			{
				switch (m_pMapdata[i][j].playerColor)
				{
				case PlayerColor::RED:
					m_renderer->DrawSolidRect(i * 4, i * 4, 0, 4, 1.0f, 0.0f, 0.0f, 1.0f);
					break;
				case PlayerColor::GREEN:
					m_renderer->DrawSolidRect(i * 4, i * 4, 0, 4, 0.0f, 1.0f, 0.0f, 1.0f);
					break;
				case PlayerColor::BLUE:
					m_renderer->DrawSolidRect(i * 4, i * 4, 0, 4, 0.0f, 0.0f, 1.0f, 1.0f);
					break;
				}
			}
		}
	}
}

void GSEGame::SetMapData(MapData (*map_data)[MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			m_pMapdata[i][j].isBomb = map_data[i][j].isBomb;
			m_pMapdata[i][j].isRock = map_data[i][j].isRock;
			m_pMapdata[i][j].item = map_data[i][j].item;
			m_pMapdata[i][j].playerColor = map_data[i][j].playerColor;
		}
	}
}
