#pragma once

#include "Renderer.h"
#include "GSEGlobal.h"

class GSELobby
{
public:
	GSELobby();
	~GSELobby();

	void RendererScene();

private:
	Renderer* m_renderer = NULL;
};

