#include "GSELobby.h"

GSELobby::GSELobby()
{
	loadingTimer = std::chrono::system_clock::now();
	m_renderer = new Renderer(GSE_WINDOW_WIDTH, GSE_WINDOW_HEIGHT);
}

GSELobby::~GSELobby()
{
}

void GSELobby::RendererScene(int num)
{
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (playerNumSave == 0)
		playerNumSave = num;

	DrawP(50.0f, 480.0f);
	DrawL(150.0f, 480.0f);
	DrawA(230.0f, 480.0f);
	DrawY(320.0f, 480.0f);
	DrawE(410.0f, 480.0f);
	DrawR(490.0f, 480.0f);

	DrawC(90.0f, 360.0f);
	DrawO(190.0f, 360.0f);
	DrawL(280.0f, 360.0f);
	DrawO(350.0f, 360.0f);
	DrawR(430.0f, 360.0f);
	
	switch (playerNumSave)
	{
	case 1:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 1.f, 0.0f, 0.0f, 1.0f);		//어두운 회색
		break;
	case 2:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 0.f, 1.0f, 0.0f, 1.0f);		//어두운 회색
		break;
	case 3:
		m_renderer->DrawSolidRect(275.0f, 160.0f, 0, 180, 180, 0.f, 0.0f, 1.0f, 1.0f);		//어두운 회색
		break;
	}
}

void GSELobby::DrawP(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f	, y - 20.0f	, 0, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y + 20.0f	, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 30.0f	, y			, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y - 20.0f	, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSELobby::DrawL(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f, y - 20.0f, 0, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y - 60.0f, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSELobby::DrawA(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f, y - 30.0f, 0, 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f, y - 30.0f, 0, 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y - 20.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y + 20.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSELobby::DrawY(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f	, y + 10.0f, 0, 20, 40, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f	, y + 10.0f, 0, 20, 40, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y - 40.0f, 0, 20, 60, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSELobby::DrawE(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f, y - 20.0f, 0, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y + 20.0f, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y - 20.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y - 60.0f, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSELobby::DrawR(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f, y - 20.0f, 0, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y + 20.0f, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 30.0f, y, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x, y - 20.0f, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f, y - 40.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 40.0f, y - 60.0f, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSELobby::DrawC(float x, float y)
{
	m_renderer->DrawSolidRect(x - 30.0f	, y - 20.0f	, 0, 20, 60, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y + 20.0f	, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y - 60.0f	, 0, 40, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 30.0f	, y			, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 30.0f	, y - 40.0f	, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}

void GSELobby::DrawO(float x, float y)
{
	m_renderer->DrawSolidRect(x - 20.0f	, y	- 20.0f	, 0, 20, 60, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x + 20.0f	, y	- 20.0f	, 0, 20, 60, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y + 20.0f	, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	m_renderer->DrawSolidRect(x			, y - 60.0f	, 0, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}
	
