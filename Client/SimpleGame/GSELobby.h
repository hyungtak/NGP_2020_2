#pragma once

#include "Renderer.h"
#include "GSEGlobal.h"

class GSELobby
{
public:
	GSELobby();
	~GSELobby();

	void RendererScene(int num);
	
private:
	int playerNumSave = 0;
	Renderer* m_renderer = NULL;
};

