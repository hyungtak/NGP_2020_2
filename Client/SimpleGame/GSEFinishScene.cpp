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

	if (num == 4)
		WinPlayer(num);
	else
		DrawPlayers();
}

void GSEFinishScene::WinPlayer(int playerNum)
{
	
	DrawW(120.0f, 480.0f);
	DrawI(260.0f, 480.0f);
	DrawN(400.0f, 480.0f);

	switch (playerNum)
	{
	case 1:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 1.f, 0.0f, 0.0f, 1.0f);		//»¡
		break;
	case 2:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 0.f, 1.0f, 0.0f, 1.0f);		//ÃÊ
		break;
	case 3:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 0.f, 0.0f, 1.0f, 1.0f);		//ÆÄ
		break;
	}
}

void GSEFinishScene::DrawPlayers()
{
	DrawD(100.0f, 480.0f);
	DrawR(200.0f, 480.0f);
	DrawA(320.0f, 480.0f);
	DrawW(440.0f, 480.0f);
}

void GSEFinishScene::DrawW(float x, float y)
{
	m_renderer->DrawSolidRect(x - 40.0f	, y - 10.0f, 0, 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y - 20.0f, 0, 20, 60, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 40.0f	, y - 10.0f, 0, 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x - 20.0f	, y - 60.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f	, y - 60.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSEFinishScene::DrawI(float x, float y)
{
	m_renderer->DrawSolidRect(x		, y - 20.0f, 0, 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x		, y	+ 20.0f, 0, 60, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x		, y - 60.0f, 0, 60, 20, 1.0f, 1.0f, 1.0f, 1.0f);

}

void GSEFinishScene::DrawN(float x, float y)
{
	m_renderer->DrawSolidRect(x - 40.0f, y - 20.0f, 0, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			,y - 20.0f, 0, 20, 60, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 40.0f, y - 20.0f, 0, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x - 20.0f, y + 20.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f, y - 60.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSEFinishScene::DrawD(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f, y - 20.0f, 0, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f, y - 20.0f, 0, 20, 60, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y - 60.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y + 20.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);

}

void GSEFinishScene::DrawR(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f, y - 20.0f, 0, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 10.0f, y + 20.0f, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 40.0f, y, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 10.0f, y - 20.0f, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f, y - 40.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 40.0f, y - 60.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSEFinishScene::DrawA(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f, y - 30.0f, 0, 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f, y - 30.0f, 0, 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y - 20.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y + 20.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}