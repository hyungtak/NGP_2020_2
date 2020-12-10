#pragma once

#include "Renderer.h"
#include "GSEGlobal.h"

class GSEFinishScene
{
public:
	GSEFinishScene();
	~GSEFinishScene();

	void RendererScene(int num);
	
	void WinPlayer(int playerNum);
	void DrawPlayers();

private:
	Renderer* m_renderer = NULL;
};

	