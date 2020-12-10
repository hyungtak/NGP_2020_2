#include "GSELobby.h"

GSELobby::GSELobby()
{
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

	m_renderer->DrawP(50.0f, 480.0f);
	m_renderer->DrawL(150.0f, 480.0f);
	m_renderer->DrawA(230.0f, 480.0f);
	m_renderer->DrawY(320.0f, 480.0f);
	m_renderer->DrawE(410.0f, 480.0f);
	m_renderer->DrawR(490.0f, 480.0f);

	m_renderer->DrawC( 90.0f, 360.0f);
	m_renderer->DrawO(190.0f, 360.0f);
	m_renderer->DrawL(280.0f, 360.0f);
	m_renderer->DrawO(350.0f, 360.0f);
	m_renderer->DrawR(430.0f, 360.0f);
	
	switch (playerNumSave)
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
