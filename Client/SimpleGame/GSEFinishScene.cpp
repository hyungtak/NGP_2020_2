#include "GSEFinishScene.h"

GSEFinishScene::GSEFinishScene()
{
	m_renderer = new Renderer(GSE_WINDOW_WIDTH, GSE_WINDOW_HEIGHT);
}

GSEFinishScene::~GSEFinishScene()
{
}

void GSEFinishScene::RendererScene(int num)
{
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (num == 3)
		DrawPlayers();
	else
		WinPlayer(num);
}

void GSEFinishScene::WinPlayer(int playerNum)
{
	
	m_renderer->DrawW(120.0f, 480.0f);
	m_renderer->DrawI(260.0f, 480.0f);
	m_renderer->DrawN(400.0f, 480.0f);

	switch (playerNum)
	{
	case 0:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 1.f, 0.0f, 0.0f, 1.0f);		//»¡
		break;
	case 1:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 0.f, 1.0f, 0.0f, 1.0f);		//ÃÊ
		break;
	case 2:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 0.f, 0.0f, 1.0f, 1.0f);		//ÆÄ
		break;
	}
}

void GSEFinishScene::DrawPlayers()
{
	m_renderer->DrawD(100.0f, 480.0f);
	m_renderer->DrawR(200.0f, 480.0f);
	m_renderer->DrawA(320.0f, 480.0f);
	m_renderer->DrawW(440.0f, 480.0f);
}
