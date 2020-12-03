#include "GSELobby.h"

GSELobby::GSELobby()
{
	m_renderer = new Renderer(GSE_WINDOW_WIDTH, GSE_WINDOW_HEIGHT);
}

GSELobby::~GSELobby()
{
}

void GSELobby::RendererScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	m_renderer->DrawSolidRect(0, 0, 0, 40, 1.0f, 1.0f, 1.0f, 1.0f);	//ÆÄ¶û
}
	