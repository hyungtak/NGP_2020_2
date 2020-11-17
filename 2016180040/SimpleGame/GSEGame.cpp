#include "stdafx.h"
#include "GSEGame.h"

GSEGame::GSEGame()
{
	//Renderer ����
	m_renderer = new Renderer(GSE_WINDOW_WIDTH, GSE_WINDOW_HEIGHT);

	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			m_pMapdata[i][j].isBomb = false;
			m_pMapdata[i][j].isRock = false;
			m_pMapdata[i][j].item = EMPTY;
		}
	}
}

GSEGame::~GSEGame()
{
	//Renderer ����
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
			if (m_pMapdata[i][j].isBomb == true)		//��ź�� ���� ���
			{

			}
			if (m_pMapdata[i][j].isRock == true)		//���� ���� ���
			{

			}
			if (m_pMapdata[i][j].item != Item::EMPTY)	//�������� ���� ���
			{

			}
		}
	}
}